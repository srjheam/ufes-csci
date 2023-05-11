#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "rbnode.h"

typedef struct rbtree {
    rbnode *root;

    compar_fn comparer;
    destruct_fn destructor;
} rbtree;

rbtree *rbtree_constructor(compar_fn compar, destruct_fn destructor);

void rbtree_insert(rbtree *tree, void *key);

void rbtree_remove(rbtree *tree, void *key);

void *rbtree_lookup(rbtree *tree, void *key);

void rbtree_clear(rbtree *tree);

void rbtree_destructor(rbtree *tree);

#endif
