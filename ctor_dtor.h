#ifndef CTOR_DTOR_H_
#define CTOR_DTOR_H

#include "stack.h"


type_error_t StackCtor(stack_t* stack, type_t start_capacity 
                       ON_DEBUG(, const char* stack_name, int line, const char* file_name, const char* function_name));

type_error_t StackDtor(stack_t* stack);

#endif //CTOR_DTOR_H