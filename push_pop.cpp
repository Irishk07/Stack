#include "push_pop.h"

#include "main.h"
#include "string_functions.h"


long StackPush(stack_t* stack, type_t new_value) {
    long code_error = SUCCESS;

    if (stack->size == stack->capacity) {
        stack->data = (char*)my_recalloc(stack->data, stack->capacity * 2, stack->capacity);

        if (stack->data == NULL) {
            code_error = code_error | RECALLOC_ERROR;
        }

        stack->capacity = stack->capacity * 2;
    }

    *(stack->data + stack->size) = new_value;

    return code_error;
}

long StackPop(stack_t* stack, type_t* delete_value) {
    long code_error = SUCCESS;

    *delete_value = *(stack->data + stack->size);

    *(stack->data + stack->size) = 0;
    stack->size -= 1;

    if (stack->size * 4 < stack->capacity) {
        stack->data = (char*)my_recalloc(stack->data, stack->capacity / 2, stack->capacity);

        if (stack->data == NULL) {
            code_error = code_error | RECALLOC_ERROR;
        }

        stack->capacity = stack->capacity / 2;
    }

    return code_error;
}