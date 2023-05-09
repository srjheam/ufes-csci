#ifndef _FLAT_SET_H_
#define _FLAT_SET_H_

#include "common.h"

typedef struct {
    byte *arr;

    size_t len;
    size_t size;

    size_t smemb;
} flat_set;

flat_set *fset_constructor(size_t smemb);

size_t fset_length(flat_set *fset);

void fset_destructor(flat_set *fset);

#endif
