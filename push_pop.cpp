#include <stdlib.h>
#include <stdio.h>

#include "push_pop.h"

#include "canary.h"
#include "check_errors.h"
#include "stack.h"
#include "string_functions.h"
#include "variable_information.h"

type_error_t StackReSize(stack_t* stack, size_t old_capacity) {
    if (stack->capacity > old_capacity) {
        type_t* temp_data = (type_t*)my_recalloc(stack->data, RealSizeStack(stack->capacity, CNT_CANARIES) * sizeof(type_t), 
                                                              RealSizeStack(old_capacity, CNT_CANARIES) * sizeof(type_t));

        if (temp_data == NULL) {
            PROPAGATE_ERROR(NOT_ENOUGH_MEMORY, free(temp_data););
        }

        stack->data = temp_data;

        init_with_poisons(stack->data + OffsetToLastElement(stack->size, CNT_CANARIES), stack->capacity - stack->size);

        ON_DEBUG(fprintf(stderr, "MEOW I'm recalloc up, I do it %zu %zu\n", stack->size, stack->capacity));
    }

    else {
        type_t* temp_data = (type_t*)my_recalloc(stack->data, RealSizeStack(stack->capacity, CNT_CANARIES) * sizeof(type_t), 
                                                              RealSizeStack(old_capacity, CNT_CANARIES) * sizeof(type_t));

        if (temp_data == NULL) {
            PROPAGATE_ERROR(NOT_ENOUGH_MEMORY, free(temp_data););
        }

        stack->data = temp_data;

        ON_DEBUG(fprintf(stderr, "MEOW I'm recalloc down, I do it %zu %zu\n", stack->size, stack->capacity);)
    }    

    ON_CANARY(SettingCanariesToEnd(stack->data, stack->capacity));

    PROPAGATE_ERROR(VERIFY(stack));

    return SUCCESS;
}


type_error_t StackPush(stack_t* stack, type_t new_value) {
    type_error_t code_error = SUCCESS;

    PROPAGATE_ERROR(VERIFY(stack));

    if (stack->size == stack->capacity) {
        size_t old_capacity = stack->capacity;
        stack->capacity *= REALLOC_COEFF;

        PROPAGATE_ERROR(StackReSize(stack, old_capacity));
    }

    *(stack->data + OffsetToNewElement(stack->size, CNT_CANARIES)) = new_value;
    stack->size++;

    PROPAGATE_ERROR(VERIFY(stack));

    return code_error;
}

type_error_t StackPeek(stack_t* stack, type_t* peek_element) {
    type_error_t code_error = SUCCESS;

    PROPAGATE_ERROR(VERIFY(stack));

    *peek_element = *(stack->data + OffsetToLastElement(stack->size, CNT_CANARIES));

    PROPAGATE_ERROR(VERIFY(stack));

    return code_error;
}

type_error_t StackPop(stack_t* stack, type_t* deleted_value) {
    type_error_t code_error = SUCCESS;

    PROPAGATE_ERROR(VERIFY(stack));

    if (stack->size == 0) {
        PROPAGATE_ERROR(POP_EMPTY_STACK);
    }

    if (deleted_value) {
        StackPeek(stack, deleted_value);
    }

    *(stack->data + OffsetToLastElement(stack->size, CNT_CANARIES)) = DEFAULT_POISON;

    stack->size--;

    if (stack->size * (REALLOC_COEFF * REALLOC_COEFF) < stack->capacity) {
        size_t old_capacity = stack->capacity;
        stack->capacity /= REALLOC_COEFF;

        PROPAGATE_ERROR(StackReSize(stack, old_capacity));
    }

    PROPAGATE_ERROR(VERIFY(stack));

    return code_error;
}