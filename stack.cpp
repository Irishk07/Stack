#include <assert.h>
#include <stdlib.h>

#include "stack.h"

#include "canary.h"
#include "check_errors.h"
#include "string_functions.h"
#include "variable_information.h"


size_t RealSizeStack(size_t capacity, size_t count_canaries) {
    return (capacity + count_canaries);
} 

size_t OffsetDueCanaries(size_t count_canaries) {
    return (count_canaries == 0) ? 0 : 1;
}

size_t OffsetToLastElement(size_t size, size_t count_canaries) {
    return size + OffsetDueCanaries(count_canaries) - 1;
}

size_t OffsetToNewElement(size_t size, size_t count_canaries) {
    return size + OffsetDueCanaries(count_canaries);
}

size_t RealIndex(size_t index, size_t count_canaries) {
    return index + OffsetDueCanaries(count_canaries);
}

type_error_t StackCtor(stack_t* stack, size_t start_capacity) { // TODO: test stack with other types than int
    assert(stack);
    assert(start_capacity > 0);

    ON_CANARY(
        stack->first_elem = CANARY;
        stack->last_elem = CANARY;
    )

    stack->capacity = start_capacity;
    stack->size = 0;

    stack->data = (type_t*)calloc(RealSizeStack(stack->capacity, CNT_CANARIES), sizeof(type_t));

    if (stack->data == NULL) {
        PROPAGATE_ERROR(NOT_ENOUGH_MEMORY);
    }

    init_with_poisons(stack->data + OffsetDueCanaries(CNT_CANARIES), (size_t)stack->capacity);

    ON_CANARY(SettingCanariesToBegin(stack->data));
    ON_CANARY(SettingCanariesToEnd(stack->data, stack->capacity));

    type_error_t code_error = VERIFY(stack);
    PROPAGATE_ERROR(code_error, free(stack->data));

    return code_error;
}

ON_DEBUG(
type_error_t StackCtorDebug(stack_t* stack, size_t start_capacity, debug_info_t my_var_info) {
    type_error_t code_error = StackCtor(stack, start_capacity);

    PROPAGATE_ERROR(VERIFY(stack));

    stack->debug_info = my_var_info;

    PROPAGATE_ERROR(VERIFY(stack));

    return code_error;
}
)

type_error_t StackDtor(stack_t* stack) {
    type_error_t code_error = VERIFY(stack);

    free(stack->data);
    
    *stack = {};

    return code_error;
}

// NOTE: example of error managment in C
// NOTE: PROPAGATE_ERROR(string[0], free_string0)

// int foo() {
//     void *string[4] = {};
//
//     string[0] = malloc(1024);
//     if (!string[0])
//         goto free_string0;
//
//     string[1] = malloc(1024);
//     if (!string[1])
//         goto free_string1;
//
//     string[2] = malloc(1024);
//     if (!string[2])
//         goto free_string2;
//
//     string[3] = malloc(1024);
//     if (!string[3])
//         goto free_string3;
//
// free_string3:
//     free(string[3]);
//
// free_string2:
//     free(string[2]);
//
// free_string1:
//     free(string[1]);
//
// free_string0:
//     free(string[0]);
//
//     return 41;
// }



// look how beautiful can it be
// int foo() {
//     void *string[4] = {};
//
//     PROPAGATE_ERROR(string[0] = malloc(1024), 0);
//     PROPAGATE_ERROR(string[1] = malloc(1124), 1);
//     PROPAGATE_ERROR(string[2] = malloc(2224), 2);
//     PROPAGATE_ERROR(string[3] = malloc(3334), 3);
//
// _3: free(string[3]);
// _2: free(string[2]);
// _1: free(string[1]);
// _0: free(string[0]);
//
//     return 41;
// }
