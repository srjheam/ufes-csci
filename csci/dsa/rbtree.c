#include "rbtree.h"

rbtree *rbtree_constructor(size_t smemb, compar_fn compar) {
    rbtree *tree = malloc(sizeof *tree);

    tree->smemb = smemb;

    tree->compar = compar;

    tree->root = NULL;

    return tree;
}

void rbtree_insert(rbtree *tree, void *key) {}

void rbtree_remove(rbtree *tree, void *key) {}

void *rbtree_lookup(rbtree *tree, void *key) {
    rbnode *curr = tree->root;
    while (curr != NULL) {
        int cmp = tree->compar(key, curr->key);
        if (cmp == 0)
            return curr->key;

        if (curr->left == NULL || curr->right == NULL) {
            curr = curr->left == NULL ? curr->right : curr->left;            
            continue;
        }

        curr = cmp < 0 ? curr->left : curr->right;
    }

    return NULL;
}

rbtree *rbtree_destructor(rbtree *tree);
