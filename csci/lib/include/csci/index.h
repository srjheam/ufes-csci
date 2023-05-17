#ifndef _INDEX_H_
#define _INDEX_H_

#include "dsa/list.h"

#include "csci/head.h"

typedef struct Index Index;

Index *index_constructor();

Head *index_add(Index *index, size_t i);

void index_remove(Index *index, size_t i);

Head *index_lookup(Index *index, size_t i);

void index_clear(Index *index);

void index_destructor(Index *index);

#endif
