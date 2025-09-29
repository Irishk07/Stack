#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdint.h>

#include "debug.h"
#include "variable_information.h"

#ifdef DEBUG
#define STACK_CREATE(stack, start_capacity) StackCtorDebug(&stack, start_capacity, {#stack, __LINE__, __func__, __FILE__})
#else // NOT DEBUG
#define STACK_CREATE(stack, start_capacity) StackCtor(&stack, start_capacity)
#endif //DEBUG

#define PROPAGATE_ERROR(error, ...)                                \
        if (error != SUCCESS) {                                    \
            ON_DEBUG(StackDump(stack, error, DUMP_VAR_INFO));      \
            __VA_ARGS__;                                           \
            return error;                                          \
        }


typedef int type_t;
const char * const TYPE_NAME = "int";

typedef uint64_t type_error_t;

const size_t DEFAULT_START_CAPACITY = 32; // it must be > 0
const size_t MAX_CAPACITY           = 1e9;

const int DEFAULT_POISON = 0XDED;


struct stack_t {
    ON_DEBUG(int first_elem);
    type_t* data = NULL;
    size_t size = 0;
    size_t capacity = 0;
    ON_DEBUG(debug_info_t debug_info);
    ON_DEBUG(int last_elem);
};


enum status {
    SUCCESS                   = 0,
    NULL_POINTER_ON_STRUCT    = 1 << 0,
    NULL_POINTER_ON_DATA      = 1 << 1,
    TOO_BIG_CAPACITY          = 1 << 2,
    TOO_BIG_SIZE              = 1 << 3,
    SIZE_BIGGER_THAN_CAPACITY = 1 << 4,
    NOT_ENOUGH_MEMORY         = 1 << 5, 
    POP_EMPTY_STACK           = 1 << 6,
    STACK_DATA_IS_POISON      = 1 << 7,
    STACK_OVERFLOW            = 1 << 8,
    CORRUPTED_CANARY          = 1 << 9
};


size_t RealSizeStack(size_t capacity, size_t cout_canaries);

size_t OffsetDueCanaries(size_t count_canaries);

size_t OffsetToLastElement(size_t size, size_t count_canaries);

type_error_t StackCtor(stack_t* stack, size_t start_capacity);

ON_DEBUG(type_error_t StackCtorDebug(stack_t* stack, size_t start_capacity, debug_info_t my_var_info));

type_error_t StackDtor(stack_t* stack);


#endif //STACK_H_