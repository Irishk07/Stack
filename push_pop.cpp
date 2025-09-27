#include <stdlib.h>
#include <stdio.h>

#include "push_pop.h"

#include "canary.h"
#include "check_errors.h"
#include "stack.h"
#include "string_functions.h"
#include "variable_information.h"


type_error_t StackPush(stack_t* stack, type_t new_value) {
    // TODO: asserts?
    type_error_t code_error = SUCCESS;

    PROPAGATE_ERROR(StackVerify(stack));

    if (stack->size == stack->capacity) {
        ssize_t temp_capacity = stack->capacity;
        stack->capacity *= realloc_coeff;

        type_t* temp_data = (type_t*)my_recalloc(stack->data, RealSizeStack(stack->capacity, cnt_canaries) * sizeof(type_t), 
                                                              RealSizeStack(temp_capacity, cnt_canaries) * sizeof(type_t));
        // TODO: stop hungarian notation!!!! it kills

        if (temp_data == NULL) {
            PROPAGATE_ERROR(NOT_ENOUGH_MEMORY, free(temp_data););
        }

        stack->data = temp_data;

        ON_DEBUG(fprintf(stderr, "I'm recalloc up, I do it %ld %ld\n", stack->size, stack->capacity);)

        initial_with_poisons(stack->data + OffsetToLastElement(stack->size, cnt_canaries), (size_t)(stack->capacity - stack->size));

        // TODO: extract setting canary to another function, in general extract all things related to canaries
        //*(stack->data + stack->capacity + 1) = (type_t)canary;
        ON_DEBUG(SettingCanariesToEnd(stack->data, stack->capacity);)
    }

    *(stack->data + OffsetToLastElement(stack->size, cnt_canaries)) = new_value;
    stack->size++;

    PROPAGATE_ERROR(StackVerify(stack));

    return code_error;
}

type_error_t StackPeek(stack_t* stack, type_t* peek_element) {
    type_error_t code_error = SUCCESS;

    PROPAGATE_ERROR(StackVerify(stack));

    *peek_element = *(stack->data + OffsetToLastElement(stack->size, cnt_canaries));

    PROPAGATE_ERROR(StackVerify(stack));

    return code_error;
}

type_error_t StackPop(stack_t* stack, type_t* deleted_value) { // TODO: delete_value rename
    // TODO: asserts
    // TODO: StackPeek - look at the top of the stack
    // TODO: allow passing delete_value == NULL
    type_error_t code_error = SUCCESS;

    PROPAGATE_ERROR(StackVerify(stack));

    if (stack->size == 0) {
        PROPAGATE_ERROR(POP_EMPTY_STACK);
    }

    stack->size--;

    if (deleted_value) {
        StackPeek(stack, deleted_value);
    }

    *(stack->data + OffsetToLastElement(stack->size, cnt_canaries)) = my_poison;

    if (stack->size * (realloc_coeff * realloc_coeff) < stack->capacity) {
        ssize_t temp_capacity = stack->capacity;
        stack->capacity /= realloc_coeff;

        type_t* temp_data = (type_t*)my_recalloc(stack->data, RealSizeStack(stack->capacity, cnt_canaries) * sizeof(type_t), 
                                                              RealSizeStack(temp_capacity, cnt_canaries) * sizeof(type_t));

        if (temp_data == NULL) {
            PROPAGATE_ERROR(NOT_ENOUGH_MEMORY, free(temp_data););
        }

        stack->data = temp_data;

        // TODO: extract setting canary to another function, in general extract all things related to canaries
        //*(stack->data + stack->capacity + 1) = (type_t)canary;
        ON_DEBUG(SettingCanariesToEnd(stack->data, stack->capacity);)

        ON_DEBUG(fprintf(stderr, "I'm recalloc down, I do it %ld %ld\n", stack->size, stack->capacity);)
    }

    ON_DEBUG(stack->first_elem = 5;)

    PROPAGATE_ERROR(StackVerify(stack));

    return code_error;
}