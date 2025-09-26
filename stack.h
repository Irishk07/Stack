#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

#ifdef DEBUG
#define ON_DEBUG(...) __VA_ARGS__
#define STACK_CREATE(stack, start_capacity, line, file_name, function_name) StackCtor(&stack, start_capacity, #stack, line, file_name, function_name)
#else
#define ON_DEBUG(...)
#define STACK_CREATE(stack, start_capacity) StackCtor(&stack, start_capacity)
#endif


typedef int type_t;
const char * const type_name = "int";

typedef long type_error_t;

const ssize_t my_start_capacity = 32; //it mustn't be <= 0
const ssize_t max_capacity      = 1e9;

const type_t poison = 666;
const type_t canary = 999;

struct VarInfo {
    const char* var_name;
    int var_line;
    const char* var_file_name;
    const char* var_function_name;
};

struct stack_t {
    type_t* data = NULL;
    ssize_t size = 0;
    ssize_t capacity = 0;
    ON_DEBUG(VarInfo now_varinfo;)
};

enum status {
    SUCCESS                   = 0,
    NULL_POINTER_ON_STACK     = 1 << 0,
    NULL_POINTER_ON_DATA      = 1 << 1,
    CAPACITY_IS_NEGATIVE      = 1 << 2,
    SIZE_IS_NEGATIVE          = 1 << 3,
    SIZE_BIGGER_THAN_CAPACITY = 1 << 4,
    RECALLOC_ERROR            = 1 << 5,
    CALLOC_ERROR              = 1 << 6,
    POP_EMPTY_STACK           = 1 << 7,
    TOO_BIG_CAPACITY          = 1 << 8,
    STACK_DATA_IS_POISON      = 1 << 9,
    CORRUPTED_FREE_PART_STACK = 1 << 10,
    CORRUPTED_CANARY          = 1 << 11
};

#endif //STACK_H_