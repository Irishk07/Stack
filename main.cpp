#include "stack.h"

#include "check_errors.h"
#include "ctor_dtor.h"
#include "push_pop.h"

int main() {

    stack_t stack = {};
    type_t delete_value = 0;

    #ifdef DEBUG
        STACK_CREATE(stack, my_start_capacity, __LINE__, __FILE__, __func__);
    #else
        STACK_CREATE(stack, my_start_capacity);
    #endif


    // for (type_t i = 0; i < 300; ++i) {
    //     StackPush(&stack, i);
    // }

    // fprintf(stderr, "\n");

    // for (type_t i = 0; i < 300; ++i) {
    //     StackPop(&stack, &delete_value);
    // }


    // for (type_t i = 0; i < 10; ++i) {
    //     StackPush(&stack, 100);
    //     StackPush(&stack, i);
    //     StackPop(&stack, &delete_value);
    // }

    
    StackDump(&stack, __LINE__, __FILE__, __func__, 0);

    StackDtor(&stack);

    return 0;
}