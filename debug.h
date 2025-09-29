#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef DEBUG
#define ON_DEBUG(...) __VA_ARGS__
#else
#define ON_DEBUG(...) 
#endif //DEBUG

#ifdef CANARIES
#define ON_CANARY(...) __VA_ARGS__
#else //CANARIES
#define ON_CANARY(...)
#endif //CANARIES

#endif //DEBUG_H_