#include "vector.h"

#define VECTOR_INITIAL_SIZE 16
#define VECTOR_GROWTH_FACTOR 2

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
    return vector->arr[idx * vector->smemb];
}

size_t vector_iterator_begin(vector *vector) { return 0; }

void *vector_iterator_next(vector *vector, size_t *saveptr) {
    void *curr = vector_index(vector, *saveptr);

    *saveptr++;

    return curr;
}

bool vector_iterator_has_next(vector *vector, size_t *saveptr) {
    return vector_length(vector) > *saveptr;
}

void vector_destructor(vector *vector) {
    size_t it = vector_iterator_begin(vector);
    while (vector_iterator_has_next(vector, &it)) {
        void *curr = vector_iterator_next(vector, &it);

        vector->destruct(curr);
    }

    free(vector->arr);

    free(vector);
}
