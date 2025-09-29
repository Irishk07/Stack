#include "check_errors.h"

#include "canary.h"
#include "stack.h"
#include "variable_information.h"


type_error_t StackVerify(stack_t* stack) {
    type_error_t code_error = SUCCESS;

    if (stack == NULL) {
        code_error |= NULL_POINTER_ON_STRUCT; 

        return code_error;
    }
            
    if (stack->data == NULL && stack->size != 0)                                                code_error |= NULL_POINTER_ON_DATA; 
    if (stack->capacity > MAX_CAPACITY)                                                         code_error |= TOO_BIG_CAPACITY;
    if (stack->size > MAX_CAPACITY)                                                             code_error |= TOO_BIG_SIZE;
    if (stack->size > stack->capacity)                                                          code_error |= SIZE_BIGGER_THAN_CAPACITY;

    if (stack->data != NULL) {
        for (size_t i = OffsetDueCanaries(CNT_CANARIES); i < stack->capacity + OffsetDueCanaries(CNT_CANARIES); ++i) {
            if (i < stack->size + OffsetDueCanaries(CNT_CANARIES) && 
                *(stack->data + i) == DEFAULT_POISON)                                           code_error |= STACK_DATA_IS_POISON;

            else if (i >= stack->size + OffsetDueCanaries(CNT_CANARIES) && 
                    *(stack->data + i) != DEFAULT_POISON)                                       code_error |= STACK_OVERFLOW;
        }

        ON_DEBUG(
        if ((*(stack->data) != CANARY) || 
            (*(stack->data + OffsetToLastElement(stack->capacity, CNT_CANARIES)) != CANARY))    code_error |= CORRUPTED_CANARY;
        )
    }

    ON_DEBUG(
    if ((stack->first_elem != CANARY) ||
        (stack->last_elem  != CANARY))                                                          code_error |= CORRUPTED_CANARY;
    )                                               

    return code_error;
}

void StackPrintError(type_error_t code_error) {
    if (code_error == SUCCESS)                  fprintf(stderr, "Not error: all right\n");
    if (code_error & NULL_POINTER_ON_STRUCT)    fprintf(stderr, "Error is: pointer on stack is NULL\n");
    if (code_error & NULL_POINTER_ON_DATA)      fprintf(stderr, "Error is: pointer on data in stack is NULL\n");
    if (code_error & TOO_BIG_CAPACITY)          fprintf(stderr, "Error is: capacity is too big\n");
    if (code_error & TOO_BIG_SIZE)              fprintf(stderr, "Error is: size is too big\n");
    if (code_error & SIZE_BIGGER_THAN_CAPACITY) fprintf(stderr, "Error is: size is bigger than capacity\n");
    if (code_error & NOT_ENOUGH_MEMORY)         fprintf(stderr, "Error is: problems with allocation memory\n");
    if (code_error & POP_EMPTY_STACK)           fprintf(stderr, "Error is: try to pop empty stack\n");
    if (code_error & STACK_DATA_IS_POISON)      fprintf(stderr, "Error is: stack data is poison\n");
    if (code_error & STACK_OVERFLOW)            fprintf(stderr, "Error is: corrupted free part of stack\n");
    if (code_error & CORRUPTED_CANARY)          fprintf(stderr, "Error is: canary is corrupted\n");
}

void StackDump(stack_t* stack, type_error_t code_error, int line, const char* function_name, const char* file_name) {
    fprintf(stderr, "%s <%s>[%p] ", "stack_t", TYPE_NAME, &stack);

    PRINT_DUMP_DEBUG_INFO(stack);
    
    fprintf(stderr, "\n    called at %s() %s:%d:\n    ", function_name, file_name, line);
    
    StackPrintError(code_error);
    
    fprintf(stderr, "    %s = %zu\n", "capacity", stack->capacity);
    fprintf(stderr, "    %s = %zu\n", "size", stack->size);
    fprintf(stderr, "    %s[%zu] = [%p] {\n", "data", stack->capacity, &(stack->data));

    ON_DEBUG(fprintf(stderr, "    +[%d] = %d (%s)\n", 0, *(stack->data), "CANARY"));
    
    for (size_t i = OffsetDueCanaries(CNT_CANARIES); i < stack->capacity + OffsetDueCanaries(CNT_CANARIES); ++i) {
        if (i >= stack->size + OffsetDueCanaries(CNT_CANARIES)) fprintf(stderr, "     [%zu] = %d (%s)\n", i, *(stack->data + i), "POISON"); // TODO make func for index
        else                                                    fprintf(stderr, "    *[%zu] = %d\n", i, *(stack->data + i));
    }

    ON_DEBUG(fprintf(stderr, "    +[%zu] = %d (%s)\n", 
             OffsetToLastElement(stack->capacity, CNT_CANARIES), *(stack->data + OffsetToLastElement(stack->capacity, CNT_CANARIES)), "CANARY"));

    fprintf(stderr, "   }\n}\n\n");
}