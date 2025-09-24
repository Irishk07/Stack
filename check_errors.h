#ifndef CHECK_ERRORS_H_
#define CHECK_ERRORS_H_

long StackVerify(stack_t* stack);

void StackPrintError(long code_error);

void StackDump(stack_t* stack);

#endif //CHECK_ERRORS_H_