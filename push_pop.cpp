#include <stdlib.h>
#include <stdio.h>

#include "push_pop.h"

#include "check_errors.h"
#include "stack.h"
#include "string_functions.h"


type_error_t StackPush(stack_t* stack, type_t new_value) {
    type_error_t code_error = SUCCESS;

    ON_DEBUG(code_error = StackVerify(stack);)

    if (code_error != SUCCESS) {
        ON_DEBUG(StackDump(stack, __LINE__, __FILE__, __func__, code_error);)

        return code_error;
    }

    if (stack->size == stack->capacity) {
        type_t* temp_point = (type_t*)my_recalloc(stack->data, (size_t)(stack->capacity * 2) * sizeof(type_t), (size_t)stack->capacity * sizeof(type_t));

        if (temp_point == NULL) {
            code_error = code_error | RECALLOC_ERROR;

            ON_DEBUG(StackDump(stack, __LINE__, __FILE__, __func__, code_error);)

            free(temp_point);
            
            return code_error;
        }

        stack->data = temp_point;
        stack->capacity = stack->capacity * 2;

        ON_DEBUG(fprintf(stderr, "I'm recalloc up, I do it %ld %ld\n", stack->size, stack->capacity);)

        init_recalloc(stack->data + stack->size, (size_t)(stack->capacity - stack->size));
    }

    *(stack->data + stack->size) = new_value;
    stack->size = stack->size + 1;

    ON_DEBUG(code_error = StackVerify(stack);)

    if (code_error != SUCCESS) {
        ON_DEBUG(StackDump(stack, __LINE__, __FILE__, __func__, code_error);)

        return code_error;
    }

    return code_error;
}

type_error_t StackPop(stack_t* stack, type_t* delete_value) {
    type_error_t code_error = SUCCESS;

    ON_DEBUG(code_error = StackVerify(stack);)

    if (code_error != SUCCESS) {
        ON_DEBUG(StackDump(stack, __LINE__, __FILE__, __func__, code_error);)

        return code_error;
    }

    if (stack->size == 0) {
        code_error = code_error | POP_EMPTY_STACK;

        ON_DEBUG(StackDump(stack, __LINE__, __FILE__, __func__, code_error);)

        return code_error;
    }

    stack->size--;

    *delete_value = *(stack->data + stack->size);

    *(stack->data + stack->size) = poison;

    if (stack->size * 4 < stack->capacity) {
        stack->data = (type_t*)my_recalloc(stack->data, (size_t)(stack->capacity / 2) * sizeof(type_t), (size_t)stack->capacity * sizeof(type_t));

        if (stack->data == NULL) {
            code_error = code_error | RECALLOC_ERROR;

            ON_DEBUG(StackDump(stack, __LINE__, __FILE__, __func__, code_error);)

            return code_error;
        }

        stack->capacity = stack->capacity / 2;

        ON_DEBUG(fprintf(stderr, "I'm recalloc down, I do it %ld %ld\n", stack->size, stack->capacity);)
    }

    ON_DEBUG(code_error = StackVerify(stack);)

    if (code_error != SUCCESS) {
        ON_DEBUG(StackDump(stack, __LINE__, __FILE__, __func__, code_error);)

        return code_error;
    }

    return code_error;
}