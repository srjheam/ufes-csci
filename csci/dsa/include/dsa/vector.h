#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "dsa/common.h"

typedef struct vector {
    byte *arr;

    size_t len;
    size_t size;

    compar_fn compar;
    copy_fn copy;
    destruct_fn destruct;

    size_t smemb;
} vector;

vector *vector_constructor(size_t smemb, compar_fn compar, copy_fn copy,
                           destruct_fn destruct);

size_t vector_length(vector *vector);

void *vector_index(vector *vector, size_t idx);

void vector_insert(vector *vector, void *elem, size_t i);

void vector_remove(vector *vector, size_t i);

size_t vector_ptrtoindex(vector *vector, void *ptr);

size_t vector_bsearch_nearest_i(vector *v, void *key);

void *vector_bsearch_nearest(vector *vector, void *key);

void *vector_bsearch(vector *vector, void *key);

void *vector_iterator_begin(vector *vector);

void *vector_iterator_forward(vector *vector, void **saveptr);

void vector_clear(vector *vector);

void vector_destructor(vector *vector);

#endif
