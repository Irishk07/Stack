#include <stdlib.h>
#include <string.h>

#include "string_functions.h"

#include "stack.h"


void init_calloc(type_t* ptr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        *(ptr++) = poison;
    }
}

void* my_recalloc(void* ptr, size_t new_size, size_t old_size) {
    char* point = (char*)realloc(ptr, new_size);

    if (new_size <= old_size) {
        return point;
    }

    if (point == NULL) {
        return NULL;
    }

    memset(point + old_size, 0, new_size - old_size);

    return point;
}

void init_recalloc(type_t* ptr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        *(ptr++) = poison;
    }
}