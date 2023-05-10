#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "rbnode.h"

typedef struct {
    rbnode *root;

    compar_fn compar;

    size_t smemb;
} rbtree;

rbtree *rbtree_constructor(size_t smemb, compar_fn compar);

void rbtree_insert(rbtree *tree, void *key);

void rbtree_remove(rbtree *tree, void *key);

void *rbtree_lookup(rbtree *tree, void *key);

rbtree *rbtree_destructor(rbtree *tree);

#endif
