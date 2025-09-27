#include <assert.h>
#include <stdlib.h>

#include "stack.h"

#include "canary.h"
#include "check_errors.h"
#include "string_functions.h"
#include "variable_information.h"


size_t RealSizeStack(ssize_t capacity, ssize_t count_canaries) {
    return (size_t)(capacity + count_canaries);
}

int OffsetDueCanaries(ssize_t count_canaries){
    return (count_canaries == 0) ? 0 : 1;
}

int OffsetToLastElement(ssize_t size, ssize_t count_canaries) {
    return (count_canaries == 0) ? (int)size : (int)size + 1;
}

type_error_t StackCtor(stack_t* stack, ssize_t start_capacity) { // TODO: test stack with other types than int
    assert(stack);
    // TODO: any start_capacity possible?

    type_error_t code_error = SUCCESS;

    ON_DEBUG(
        stack->first_elem = canary;
        stack->last_elem = canary;
    )
    stack->capacity = start_capacity;
    stack->size = 0;

    stack->data = (type_t*)calloc(RealSizeStack(stack->capacity, cnt_canaries), sizeof(type_t)); // TODO: why 2?

    // TODO: test what happens if calloc fails?
    if (stack->data == NULL) {
        PROPAGATE_ERROR(NOT_ENOUGH_MEMORY);
    }

    initial_with_poisons(stack->data + OffsetDueCanaries(cnt_canaries), (size_t)stack->capacity);

    // TODO: extract setting canary to another function, in general extract all things related to canaries
    // *(stack->data) = (type_t)canary;
    ON_DEBUG(SettingCanariesToBegin(stack->data);)
    // *(stack->data + stack->capacity + 1) = (type_t)canary;
    ON_DEBUG(SettingCanariesToEnd(stack->data, stack->capacity);)

    // NOTE: You can make a macro "PROPAGATE_ERROR(error)"
    // NOTE: E.g. PROPAGATE_ERROR(StackVerify()); // if (error) return error;

    // FIXME ON_DEBUG need? (stackverify and stackdump)
    code_error |= StackVerify(stack);
    PROPAGATE_ERROR(code_error, free(stack->data););

    return code_error;
}

ON_DEBUG(
type_error_t StackFillVarInfo(stack_t* stack, var_info my_var_info) {
    type_error_t code_error = SUCCESS;

    PROPAGATE_ERROR(StackVerify(stack));

    stack->now_var_info = my_var_info;

    PROPAGATE_ERROR(StackVerify(stack));

    return code_error;
}
)



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



// TODO: look how beautiful can it be
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


type_error_t StackDtor(stack_t* stack) {
    type_error_t code_error = SUCCESS;

    ON_DEBUG(code_error = StackVerify(stack);)

    free(stack->data);
    
    *stack = {};

    return code_error;
}