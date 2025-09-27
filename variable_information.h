#ifndef VARIABLE_INFORMATION_H_
#define VARIABLE_INFORMATION_H_

#include "stack.h"

#define DUMP_VAR_INFO __LINE__, __func__, __FILE__

#ifdef DEBUG
#define PRINT_DUMP_VAR_INFO(stack) fprintf(stderr, "\"%s\" %s() %s:%d {",                               \
                                           stack->now_var_info.name, stack->now_var_info.function_name, \
                                           stack->now_var_info.file_name, stack->now_var_info.line);
#else
#define PRINT_DUMP_VAR_INFO(stack)
#endif //DEBUG


struct var_info { // TODO: naming 
    const char* name;
    int line;
    const char* function_name;
    const char* file_name;
};


#endif //VARIABLE_INFORMATION_H_