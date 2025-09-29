#ifndef PUSH_POP_H_
#define PUSH_POP_H_

#include "stack.h"


const int REALLOC_COEFF = 2;


type_error_t StackReSize(stack_t* stack, size_t old_capacity);

type_error_t StackPush(stack_t* stack, type_t new_value);

type_error_t StackPeek(stack_t* stack, type_t* peek_element);

type_error_t StackPop(stack_t* stack, type_t* delete_value);


#endif //PUSH_POP_H_