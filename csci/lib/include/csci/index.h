#ifndef _INDEX_H_
#define _INDEX_H_

#include "dsa/list.h"

typedef struct Index Index;

Index *index_constructor(compar_fn compar);

list *index_add(Index *index, size_t i, compar_fn compar, copy_fn copy,
                destruct_fn destruct);

void index_remove(Index *index, size_t i);

list *index_lookup(Index *index, size_t i);

void index_clear(Index *index);

void index_destructor(Index *index);

#endif
