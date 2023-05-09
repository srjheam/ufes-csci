#include "flat_set.h"

#define FLAT_SET_INITIAL_SIZE 16
#define FLAT_SET_GROWTH_FACTOR 2

flat_set *fset_constructor(size_t smemb, compar_fn compar, copy_fn copy,
                           destruct_fn destruct) {
    flat_set *fset = malloc(sizeof *fset);

    fset->smemb = smemb;

    fset->compar = compar;
    fset->copy = copy;
    fset->destruct = destruct;

    fset->size = FLAT_SET_INITIAL_SIZE;
    fset->len = 0;
    fset->arr = malloc(fset->size * smemb);

    return fset;
}

size_t fset_length(flat_set *fset) { return fset->len; }

void *fset_index(flat_set *fset, size_t idx) {
    return fset->arr[idx * fset->smemb];
}

size_t fset_iterator_begin(flat_set *fset) { return 0; }

void *fset_iterator_next(flat_set *fset, size_t *saveptr) {
    void *curr = fset_index(fset, *saveptr);

    *saveptr++;

    return curr;
}

bool fset_iterator_has_next(flat_set *fset, size_t *saveptr) {
    return fset_length(fset) > *saveptr;
}

void fset_destructor(flat_set *fset) {
    size_t it = fset_iterator_begin(fset);
    while (fset_iterator_has_next(fset, &it)) {
        void *curr = fset_iterator_next(fset, &it);

        fset->destruct(curr);
    }

    free(fset->arr);

    free(fset);
}
