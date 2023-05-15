#include "dsa/exceptions.h"

#include "dsa/vector.h"

#define VECTOR_INITIAL_SIZE 16
#define VECTOR_GROWTH_FACTOR 2

void __vector_resize(vector *vector, size_t nsize) {
    vector->size = nsize;
    vector->arr = realloc(vector->arr, vector->size * vector->smemb);
}

void __vector_grow(vector *vector) {
    if (vector->len + 1 >= vector->size) {
        __vector_resize(vector, vector->size << 1);
    }
}

void __vector_shrink(vector *vector) {
    if (vector->size > VECTOR_INITIAL_SIZE &&
        vector->len <= 6 * (vector->size >> 4)) {
        __vector_resize(vector, vector->size >> 1);
    }
}

vector *vector_constructor(size_t smemb, compar_fn compar, copy_fn copy,
                           destruct_fn destruct) {
    vector *vector = malloc(sizeof *vector);

    vector->smemb = smemb;

    vector->compar = compar;
    vector->copy = copy;
    vector->destruct = destruct;

    vector->size = VECTOR_INITIAL_SIZE;
    vector->len = 0;
    vector->arr = malloc(vector->size * smemb);

    return vector;
}

size_t vector_length(vector *vector) { return vector->len; }

void *vector_index(vector *vector, size_t idx) {
    return &vector->arr[idx * vector->smemb];
}

void vector_insert(vector *vector, void *elem, size_t i) {
    if (i >= vector->len)
        exception_throw_index("vector_insert");

    __vector_grow(vector);

    memmove(vector->arr + (i + 1) * vector->smemb,
            vector->arr + i * vector->smemb, (vector->len - i) * vector->smemb);
    memcpy(vector->arr + i * vector->smemb, elem, vector->smemb);

    vector->len++;
}

void vector_remove(vector *vector, size_t i) {
    if (i >= vector->len)
        exception_throw_index("vector_remove");

    __vector_shrink(vector);

    vector->destruct(vector->arr + i * vector->smemb);

    memmove(vector->arr + i * vector->smemb,
            vector->arr + (i + 1) * vector->smemb,
            (vector->len - i - 1) * vector->smemb);

    vector->len--;
}

void *vector_bsearch_nearest(vector *v, void *key) {
    size_t l = 0;
    size_t r = v->len - 1;

    int *cmp = 1;
    while (l <= r) {
        size_t m = l + (r - l) / 2;

        void *t = v->arr + m * v->smemb;

        *cmp = v->compar(t, key);

        if (*cmp < 0) {
            l = m + 1;
        } else if (*cmp > 0) {
            r = m - 1;
        } else {
            return t;
        }
    }

    return v->arr + l * v->smemb;
}

void *vector_bsearch(vector *vector, void *key) {
    return bsearch(key, vector->arr, vector->len, vector->smemb,
                   vector->compar);
}

void *vector_iterator_begin(vector *vector) { return vector->arr; }

void *vector_iterator_forward(vector *vector, void **saveptr) {
    if (vector->arr + vector->len * vector->smemb == *saveptr)
        return NULL;

    void *r = *saveptr;

    *saveptr = *(byte **)saveptr + vector->smemb;
    return r;
}

void vector_clear(vector *vector) {
    for (void *it = vector_iterator_begin(vector); it;
         it = vector_iterator_forward(vector, &it))
        vector->destruct(it);

    vector->len = 0;
    __vector_resize(vector, VECTOR_INITIAL_SIZE);
}

void vector_destructor(vector *vector) {
    if (vector->destruct != NULL)
        vector_clear(vector);

    free(vector->arr);

    free(vector);
}
