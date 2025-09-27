#include "check_errors.h"
#include "debug.h"
#include "push_pop.h"
#include "stack.h"


int main() {

    stack_t stack = {};
    type_t delete_value = 0;

    STACK_CREATE(stack, my_start_capacity);

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
    
    ON_DEBUG(StackDump(&stack, 0, DUMP_VAR_INFO);)

    StackDtor(&stack);

    return 0;
}