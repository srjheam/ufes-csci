#include "assert.h"

#include "dsa/vector.h"

#include "csci/common.h"

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
    size_t i = vector_ptrtoindex(index->vector, found);
    if (i < index->vector->len)
        return found;

    vector_insert(index->vector, &head, i);
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

void index_clear(Index *index) {
    for (Head *it = vector_iterator_begin(index->vector); it;
         it = vector_iterator_forward(index->vector, &it)) {
        list_destructor(it->head);
        it->head = NULL;
    }
}

void index_destructor(Index *index) {
    index_clear(index);
    vector_destructor(index->vector);

    free(index);
}
