#include "check_errors.h"

#include "stack.h"


type_error_t StackVerify(stack_t* stack) {
    type_error_t code_error = SUCCESS;

    if (stack == NULL)                                            code_error = code_error | NULL_POINTER_ON_STACK;
    if (stack->data == NULL && stack->size != 0)                  code_error = code_error | NULL_POINTER_ON_DATA; 
    if (stack->capacity > max_capacity)                           code_error = code_error | TOO_BIG_CAPACITY;
    if (stack->capacity < 0)                                      code_error = code_error | CAPACITY_IS_NEGATIVE;
    if (stack->size < 0)                                          code_error = code_error | SIZE_IS_NEGATIVE;
    if (stack->size > stack->capacity)                            code_error = code_error | SIZE_BIGGER_THAN_CAPACITY;

    for (ssize_t i = 0; i < stack->capacity; ++i) {
        if (i < stack->size && *(stack->data + i) == poison)     code_error = code_error | STACK_DATA_IS_POISON;

        else if (i >= stack->size && *(stack->data + i) != poison) code_error = code_error | CORRUPTED_FREE_PART_STACK;
    }

    return code_error;
}

void StackPrintError(type_error_t code_error) {
    if (code_error & NULL_POINTER_ON_STACK)     fprintf(stderr, "Error is: pointer on stack is NULL\n");
    if (code_error & NULL_POINTER_ON_DATA)      fprintf(stderr, "Error is: pointer on data in stack is NULL\n");
    if (code_error & CAPACITY_IS_NEGATIVE)      fprintf(stderr, "Error is: capacity is negative\n");
    if (code_error & SIZE_IS_NEGATIVE)          fprintf(stderr, "Error is: size if negative\n");
    if (code_error & SIZE_BIGGER_THAN_CAPACITY) fprintf(stderr, "Error is: size is bigger than capacity\n");
    if (code_error & RECALLOC_ERROR)            fprintf(stderr, "Error is: problems with allocation memory\n");
    if (code_error & CALLOC_ERROR)              fprintf(stderr, "Error is: problems with allocation memory\n");
    if (code_error & POP_EMPTY_STACK)           fprintf(stderr, "Error is: try to pop empty stack\n");
    if (code_error & TOO_BIG_CAPACITY)          fprintf(stderr, "Error is: capacity is too big\n");
    if (code_error & STACK_DATA_IS_POISON)      fprintf(stderr, "Error is: stack data is poison\n");
    if (code_error & CORRUPTED_FREE_PART_STACK) fprintf(stderr, "Error is: corrupted free part of stack\n");
}

void StackDump(stack_t* stack, int line, const char* file_name, const char* function_name, type_error_t code_error) {
    fprintf(stderr, "%s <%s>[%p] ", 
           "stack_t", type_name, &stack);
    ON_DEBUG(fprintf(stderr, "\"%s\" %s() %s:%d {",  stack->now_varinfo.var_name, stack->now_varinfo.var_function_name, stack->now_varinfo.var_file_name, stack->now_varinfo.var_line);)
    fprintf(stderr, "\n    called at %s() %s:%d:\n", function_name, file_name, line);
    StackPrintError(code_error);
    fprintf(stderr, "    %s = %ld\n", "capacity", stack->capacity);
    fprintf(stderr, "    %s = %ld\n", "size", stack->size);
    fprintf(stderr, "    %s[%ld] = [%p] {\n", "data", stack->capacity, &(stack->data));
    
    for (int i = 0; i < stack->capacity; ++i) {
        if (i >= stack->size) fprintf(stderr, "     [%d] = %d (%s)\n", i, *(stack->data + i), "POISON");
        else                 fprintf(stderr, "    *[%d] = %d\n", i, *(stack->data + i));
    }

    printf("   }\n}\n\n");
}