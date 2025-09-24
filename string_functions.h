#ifndef STRING_FUNCTIONS_H_
#define STRING_FUNCTIONS_H_

#include <stdio.h>

#include "stack.h"


const int SIZE_OF_BUF = 256;
const int ZERO = 0;
const int CNT_SYMBOLS = 256;


void init_calloc(type_t* ptr, size_t size);

void *my_recalloc(void *ptr, size_t new_size, size_t old_size);

void init_recalloc(type_t* ptr, size_t size);

#endif //STRING_FUNCTIONS_H_