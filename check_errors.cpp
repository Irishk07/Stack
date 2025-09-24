#include "check_errors.h"

#include "main.h"


long StackVerify(stack_t* stack) {
    long code_error = SUCCESS;

    if (stack == NULL) {
        code_error = code_error | NULL_POINTER_ON_STACK;
    }

    if (stack->data == NULL) {
        code_error = code_error | NULL_POINTER_ON_DATA; 
    }

    if (stack->capacity < 0) {
        code_error = code_error | CAPACITY_IS_NEGATIVE;
    }

    if (stack->size < 0) {
        code_error = code_error | SIZE_IS_NEGATIVE;
    }

    if (stack->size > stack->capacity) {
        code_error = code_error | SIZE_BIGGER_THAN_CAPACITY;
    }

    return code_error;
}

void StackPrintError(long code_error) {
    if (code_error & NULL_POINTER_ON_STACK) {
        printf("%s\n", "Error is: pointer on stack is NULL");
    }

    if (code_error & NULL_POINTER_ON_DATA) {
        printf("%s\n", "Error is: pointer on data in stack is NULL");
    }

    if (code_error & CAPACITY_IS_NEGATIVE) {
        printf("%s\n", "Error is: capacity is negative");
    }

    if (code_error & SIZE_IS_NEGATIVE) {
        printf("%s\n", "Error is: size if negative");
    }

    if (code_error & SIZE_BIGGER_THAN_CAPACITY) {
        printf("%s\n", "Error is: size is bigger than capacity");
    }

    if (code_error & RECALLOC_ERROR) {
        printf("%s\n", "Error is: problems with allocation memory");
    }

    if (code_error & CALLOC_ERROR) {
        printf("%s\n", "Error is: problems with allocation memory");
    }
}

void StackDump(stack_t* stack) {
    printf("%c <%c>[%p] \"%c\" {\n", type_stack_name, type_name, &stack, stack_name);
    printf("%c = %zu\n", capacity_name, stack->capacity);
    printf("%c = %zu\n", size_name, stack->size);
    printf("%c[%zu] = [%p] {\n", array_name, stack->capacity, &(stack->data));
    
    for (int i = 0; i < stack->capacity; ++i) {
        printf("*[%d] = %d\n", i, *(stack->data + i));
    }

    printf("}\n}");
}