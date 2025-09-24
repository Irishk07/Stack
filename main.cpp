#include "stack.h"

#include "check_errors.h"
#include "ctor_dtor.h"
#include "push_pop.h"

int main() {

    stack_t stack = {};
    type_t delete_value = 0;

    #ifdef DEBUG
        STACK_CREATE(stack, __LINE__, __FILE__, __func__);
    #else
        STACK_CREATE(stack);
    #endif

    StackPush(&stack, 5);
    StackPush(&stack, 9);
    StackPush(&stack, 17);

    StackPop(&stack, &delete_value);

    StackPush(&stack, 20);

    StackDump(&stack, __LINE__, __FILE__, __func__, 0);

    StackDtor(&stack);

    return 0;
}