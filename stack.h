#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

#include "debug.h"
#include "variable_information.h"

#ifdef DEBUG
#define STACK_CREATE(stack, start_capacity) StackCtor(&stack, start_capacity), \
                                            StackFillVarInfo(&stack, {#stack, __LINE__, __func__, __FILE__})
#else
#define STACK_CREATE(stack, start_capacity) StackCtor(&stack, start_capacity)
#endif //DEBUG

#define PROPAGATE_ERROR(error, ...)                                \
        if (error != SUCCESS) {                                    \
            ON_DEBUG(StackDump(stack, error, DUMP_VAR_INFO);)      \
            __VA_ARGS__                                            \
            return error;                                          \
        }


typedef int type_t;
const char * const type_name = "int";

typedef __uint64_t type_error_t; // TODO: use unsigned types for bit operations. use fixed-width integer type, like uint64_t

const ssize_t my_start_capacity = 32; //it mustn't be <= 0 // TODO: size_t
const ssize_t max_capacity      = 1e9;

const int my_poison = 0XDED;


struct stack_t {
    ON_DEBUG(int first_elem;)
    type_t* data = NULL;
    ssize_t size = 0;
    ssize_t capacity = 0;
    ON_DEBUG(var_info now_var_info;)
    ON_DEBUG(int last_elem;)
};


enum status {
    SUCCESS                   = 0,
    NULL_POINTER_ON_STRUCT    = 1 << 0, // TODO: naming
    NULL_POINTER_ON_DATA      = 1 << 1, // TODO: naming
    CAPACITY_IS_NEGATIVE      = 1 << 2,
    SIZE_IS_NEGATIVE          = 1 << 3,
    SIZE_BIGGER_THAN_CAPACITY = 1 << 4,
    NOT_ENOUGH_MEMORY         = 1 << 5, 
    POP_EMPTY_STACK           = 1 << 6,
    TOO_BIG_CAPACITY          = 1 << 7,
    STACK_DATA_IS_POISON      = 1 << 8, // TODO: this is not an error?
    STACK_OVERFLOW            = 1 << 9, // TODO: naming
    CORRUPTED_CANARY          = 1 << 10
};

size_t RealSizeStack(ssize_t capacity, ssize_t cout_canaries);

int OffsetDueCanaries(ssize_t count_canaries);

int OffsetToLastElement(ssize_t size, ssize_t count_canaries);

type_error_t StackCtor(stack_t* stack, ssize_t start_capacity);

ON_DEBUG(type_error_t StackFillVarInfo(stack_t* stack, var_info my_var_info);)

type_error_t StackDtor(stack_t* stack);


#endif //STACK_H_