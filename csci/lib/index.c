#include "dsa/vector.h"

#include "csci/common.h"
#include "csci/head.h"

#include "csci/index.h"

struct Index {
    vector *vector;
};

Index *index_constructor(compar_fn compar) {
    Index *index = malloc(sizeof *index);

    index->vector =
        vector_constructor(sizeof(Head), (compar_fn)head_compar, NULL, NULL);

    return index;
}

list *index_add(Index *index, size_t i, compar_fn compar, copy_fn copy,
                destruct_fn destruct) {
    Head head = {.i = i, .v = NULL};

    Head *found = vector_bsearch(index->vector, &head);
    if (found)
        return found->v;

    head.v = list_constructor(compar, copy, destruct);

    int i = (vector_bsearch_nearest(index->vector, &head) -
             vector_iterator_begin(index->vector)) /
            index->vector->smemb;

    vector_insert(index->vector, &head, i);
}

void index_remove(Index *index, size_t i) {}

list *index_lookup(Index *index, size_t i) {
    Head head = {.i = i, .v = NULL};

    Head *found = vector_bsearch(index->vector, &head);

    if (!found) {
        return NULL;
    }

    return found->v;
}

void index_clear(Index *index) {
    for (Head *it = vector_iterator_begin(index->vector); it;
         it = vector_iterator_forward(index->vector, &it)) {
        list_destructor(it->v);
        it->v = NULL;
    }
}

void index_destructor(Index *index) {
    index_clear(index);
    vector_destructor(index->vector);

    free(index);
}
