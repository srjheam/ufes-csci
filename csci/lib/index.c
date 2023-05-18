#include "assert.h"

#include "dsa/vector.h"

#include "csci/index.h"

struct Index {
    vector *vector;
};

Index *index_constructor() {
    Index *index = malloc(sizeof *index);

    index->vector =
        vector_constructor(sizeof(Head), (compar_fn)head_compar, NULL, NULL);

    return index;
}

Head *index_add(Index *index, size_t i) {
    Head head = {.i = i, .head = NULL};

    Head *found = vector_bsearch_nearest(index->vector, &head);
    size_t idx = vector_ptrtoindex(index->vector, found);
    if (i == found->i)
        return found;

    vector_insert(index->vector, &head, idx);

    return vector_index(index->vector, idx);
}

void index_remove(Index *index, size_t i) {
    Head head = {.i = i, .head = NULL};

    Head *found = vector_bsearch(index->vector, &head);
    if (!found)
        return;

    assert(found->head == NULL);

    vector_remove(index->vector, vector_ptrtoindex(index->vector, found));
}

Head *index_lookup(Index *index, size_t i) {
    Head head = {.i = i, .head = NULL};

    Head *found = vector_bsearch(index->vector, &head);

    return found;
}

void index_destructor(Index *index) {
    vector_destructor(index->vector);

    free(index);
}
