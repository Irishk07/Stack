#ifndef PUSH_POP_H_
#define PUSH_POP_H_

#include "stack.h"


const int realloc_coeff = 2;


type_error_t StackPush(stack_t* stack, type_t new_value);

type_error_t StackPeek(stack_t* stack, type_t* peek_element);

type_error_t StackPop(stack_t* stack, type_t* delete_value);


#endif //PUSH_POP_H_