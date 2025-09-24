#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>


typedef int type_t;

const char* type_stack_name = "stack_t";
const char* type_name = "int";
const char* stack_name = "stack";
const char* capacity_name = "capacity";
const char* size_name = "size";
const char* array_name = "data";

struct stack_t {
    char* data = NULL;
    size_t size = 0;
    size_t capacity = 0;
};

enum status {
    SUCCESS                   = 0,
    NULL_POINTER_ON_STACK     = 1 << 0,
    NULL_POINTER_ON_DATA      = 1 << 1,
    CAPACITY_IS_NEGATIVE      = 1 << 2,
    SIZE_IS_NEGATIVE          = 1 << 3,
    SIZE_BIGGER_THAN_CAPACITY = 1 << 4,
    RECALLOC_ERROR            = 1 << 5,
    CALLOC_ERROR              = 1 << 6
};

#endif //MAIN_H_