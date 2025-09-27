#ifndef CANARY_H_
#define CANARY_H_

#include <stdio.h>

#include "stack.h"

#ifdef DEBUG
const ssize_t cnt_canaries = 2;
#else
const ssize_t cnt_canaries = 0;
#endif //DEBUG


const int canary = 0XEDA; // TODO: what if type_t is not an integer type?


void SettingCanariesToBegin(type_t* ptr);

void SettingCanariesToEnd(type_t* ptr, ssize_t capacity);


#endif //CANARY_H_