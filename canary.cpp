#include <stdio.h>

#include "canary.h"

#include "stack.h"


void SettingCanariesToBegin(type_t* ptr) {
    *ptr = (type_t)canary;
}

void SettingCanariesToEnd(type_t* ptr, ssize_t capacity) {
    *(ptr + capacity + 1) = (type_t)canary;
}