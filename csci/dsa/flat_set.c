#include "flat_set.h"

#define FLAT_SET_INITIAL_SIZE 16
#define FLAT_SET_GROWTH_FACTOR 2

flat_set *fset_constructor(size_t smemb) {
    flat_set *fset = malloc(sizeof *fset);

    fset->smemb = smemb;

    fset->size = FLAT_SET_INITIAL_SIZE;
    fset->len = 0;
    fset->arr = malloc(fset->size * smemb);

    return fset;
}

size_t fset_length(flat_set *fset) { return fset->len; }

void fset_destructor(flat_set *fset) {
    free(fset->arr);

    free(fset);
}
