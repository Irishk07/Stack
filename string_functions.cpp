#include <stdlib.h>
#include <string.h>

#include "string_functions.h"

#include "stack.h"


void* my_recalloc(void* ptr, size_t new_size, size_t old_size) {
    // TODO: asserts: size > 0, size < dofiga, ptr != NULL, ...
    char* point = (char*)realloc(ptr, new_size);

    if (new_size <= old_size) {
        return point;
    }

    if (point == NULL) { // TODO: hoist
        return NULL;
    }

    memset(point + old_size, 0, new_size - old_size);

    return point;
}

void initial_with_poisons(type_t* ptr, size_t size) { 
    // TODO: assert for ptr and for size?
    for (size_t i = 0; i < size; ++i) {
        *(ptr + i) = my_poison;
    }
}

// FUN NOTE: malloc + memset to fail fast? 