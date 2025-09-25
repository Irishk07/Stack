#include <assert.h>
#include <stdlib.h>

#include "check_errors.h"
#include "ctor_dtor.h"
#include "string_functions.h"

#include "stack.h"


type_error_t StackCtor(stack_t* stack, type_t start_capacity ON_DEBUG(, const char* stack_name, int line, const char* file_name, const char* function_name)) {
    assert(stack);

    type_error_t code_error = SUCCESS;

    stack->capacity = start_capacity;
    stack->size = 0;

    ON_DEBUG(
    stack->now_varinfo.var_name          = stack_name;
    stack->now_varinfo.var_line          = line;
    stack->now_varinfo.var_file_name     = file_name;
    stack->now_varinfo.var_function_name = function_name;
    )

    stack->data = (type_t*)calloc((size_t)stack->capacity, sizeof(type_t));

    if (stack->data == NULL) {
        code_error = code_error | CALLOC_ERROR;

        ON_DEBUG(StackDump(stack, __LINE__, __FILE__, __func__, code_error);)
    }

    init_calloc(stack->data, (size_t)stack->capacity);

    ON_DEBUG(code_error = code_error | StackVerify(stack);)

    if (code_error != SUCCESS) {
        ON_DEBUG(StackDump(stack, __LINE__, __FILE__, __func__, code_error);)

        free(stack->data);
    }

    return code_error;
}

type_error_t StackDtor(stack_t* stack) {
    type_error_t code_error = SUCCESS;

    ON_DEBUG(code_error = StackVerify(stack);)

    free(stack->data);
    stack->data = NULL;

    stack->capacity = 0;
    stack->size = 0;

    return code_error;
}