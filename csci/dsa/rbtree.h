#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "rbnode.h"

typedef struct {
    rbnode *root;

    size_t smemb;
} rbtree;

void rbtree_insert(rbtree *tree, void *key);

void rbtree_remove(rbtree *tree, void *key);

void *rbtree_lookup(rbtree *tree, void *key, compar_fn compar);

void rbnode_rotateleft(rbnode *root);

void rbnode_rotateright(rbnode *root);

#endif
