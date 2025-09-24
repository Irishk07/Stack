#include <stdlib.h>

#include "ctor_dtor.h"

#include "main.h"


long StackCtor(stack_t* stack) {
    long code_error = SUCCESS;

    stack->capacity = 32;
    stack->size = 0;

    stack->data = (char*)calloc(stack->capacity, sizeof(type_t));

    if (stack->data == NULL) {
        code_error = code_error | CALLOC_ERROR;
    }

    return code_error;
}

void StackDtor(stack_t* stack) {
    free(stack->data);
}