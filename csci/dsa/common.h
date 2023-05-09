#ifndef _COMMON_H_
#define _COMMON_H_

#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

typedef unsigned char byte;

typedef int (*compar_fn)(const void *, const void *);

typedef void *(*copy_fn)(const void *);

typedef void (*destruct_fn)(void *);

#endif
