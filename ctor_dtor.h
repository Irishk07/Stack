#ifndef CTOR_DTOR_H_
#define CTOR_DTOR_H

#include "stack.h"


type_error_t StackCtor(stack_t* stack, int line, const char* file_name, const char* function_name);

type_error_t StackDtor(stack_t* stack);

#endif //CTOR_DTOR_H