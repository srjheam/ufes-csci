#ifndef _FLAT_SET_H_
#define _FLAT_SET_H_

#include "common.h"

typedef struct {
    byte *arr;

    size_t len;
    size_t size;

    compar_fn compar;
    copy_fn copy;
    destruct_fn destruct;

    size_t smemb;
} flat_set;

flat_set *fset_constructor(size_t smemb, compar_fn compar, copy_fn copy,
                           destruct_fn destruct);

size_t fset_length(flat_set *fset);

void *fset_index(flat_set *fset, size_t idx);

void fset_push(flat_set *fset, void *elem);

size_t fset_iterator_begin(flat_set *fset);

void *fset_iterator_next(flat_set *fset, size_t *saveptr);

bool fset_iterator_has_next(flat_set *fset, size_t *saveptr);

void fset_destructor(flat_set *fset);

#endif
