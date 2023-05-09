#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "common.h"

typedef struct {
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

void vector_push(vector *vector, void *elem);

size_t vector_iterator_begin(vector *vector);

void *vector_iterator_next(vector *vector, size_t *saveptr);

bool vector_iterator_has_next(vector *vector, size_t *saveptr);

void vector_destructor(vector *vector);

#endif
