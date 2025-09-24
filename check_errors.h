#ifndef CHECK_ERRORS_H_
#define CHECK_ERRORS_H_

#include "stack.h"


type_error_t StackVerify(stack_t* stack);

void StackPrintError(type_error_t code_error);

void StackDump(stack_t* stack, int line, const char* file_name, const char* function_name, type_error_t code_error);

#endif //CHECK_ERRORS_H_