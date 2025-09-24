#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

#ifdef DEBUG
#define ON_DEBUG(...) __VA_ARGS__
#else
#define ON_DEBUG(...)
#endif


typedef int type_t;
const char * const type_name = "int";

typedef long type_error_t;

const int start_capacity = 32; //it mustn't be <= 0
const int max_capacity   = 1e9;

const int poison = 666;

struct VarInfo {
    int val_line;
    const char* val_file_name;
    const char* val_function_name;
};

struct stack_t {
    type_t* data = NULL;
    ssize_t size = 0;
    ssize_t capacity = 0;
    VarInfo now_varinfo;
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
    CORRUPTED_FREE_PART_STACK = 1 << 10
};

#endif //STACK_H_