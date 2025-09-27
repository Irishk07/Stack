#ifndef CHECK_ERRORS_H_
#define CHECK_ERRORS_H_

#include "stack.h"


type_error_t StackVerify(stack_t* stack);

void StackPrintError(type_error_t code_error);

void StackDump(stack_t* stack, type_error_t code_error, int line, const char* function_name, const char* file_name);


#endif //CHECK_ERRORS_H_