#include <stdio.h>

#ifndef _DEBUG_IONCE
#define _DEBUG_IONCE

#define debug_int(var) { printf(#var); printf(" = %d \n", var); }
#define debug(str, ...) { printf(#str, ##__VA_ARGS__); printf("\n"); }

#endif
