#include "rbtree.h"

rbnode *__rbtree_fixup(rbnode *node) {
    while (node->parent != NULL && node->parent->color == RED) {
        rbnode *grandparent = node->parent->parent;
        rbnode *uncle = grandparent->left == node->parent
            ? grandparent->right
            : grandparent->left;

        if (uncle != NULL && uncle->color == RED) {
            node->parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;

            node = grandparent;
            continue;
        }

        if (node->parent->left == node) {
            if (grandparent->left == node->parent) {
                rbnode *x = rbnode_rotateright(grandparent);

                grandparent->color = RED;
                x->color = BLACK;

                node = x;
                continue;
            }

            rbnode *x = rbnode_rotateleft(node->parent);

            node = x->left;
            continue;
        }

        if (grandparent->right == node->parent) {
            rbnode *x = rbnode_rotateleft(grandparent);

            grandparent->color = RED;
            x->color = BLACK;

            node = x;
            continue;
        }

        rbnode *x = rbnode_rotateright(node->parent);

        node = x->right;
    }

    node->color = BLACK;

    while (node->parent != NULL)
        node = node->parent;

    return node;
}

rbtree *rbtree_constructor(compar_fn compar, destruct_fn destructor) {
    rbtree *tree = malloc(sizeof *tree);

    tree->comparer = compar;
    tree->destructor = destructor;

    tree->root = NULL;

    return tree;
}

void rbtree_insert(rbtree *tree, void *key) {
    if (tree->root == NULL) {
        tree->root = rbnode_constructor(key, NULL, NULL, NULL, BLACK);
        return;
    }

    rbnode *curr = tree->root;
    rbnode *prev = NULL;
    while (curr != NULL) {
        int cmp = tree->comparer(key, curr->key);

        prev = curr;
        curr = cmp < 0 ? curr->left : curr->right;
    }

    rbnode *node = rbnode_constructor(key, prev, NULL, NULL, RED);
    if (tree->comparer(key, prev->key) < 0) {
        prev->left = node;
    } else {
        prev->right = node;
    }

    tree->root = __rbtree_fixup(node);
}

/**
 * @brief Lookup for a @p key in @p rbtree
 *
 * @param tree The binary tree
 * @param key The key to look for
 */
void *rbtree_lookup(rbtree *tree, void *key) {
    rbnode *curr = tree->root;
    while (curr != NULL) {
        int cmp = tree->comparer(key, curr->key);
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

void *rbtree_iterator_begin(rbtree *tree) {
    return rbnode_iterator_begin(tree->root);
}

void *rbtree_iterator_next(void **saveptr) {
    return rbnode_iterator_next(saveptr);
}

bool rbtree_iterator_has_next(void **saveptr) {
    return rbnode_iterator_has_next(saveptr);
}

void rbtree_clear(rbtree *tree) {
    rbnode_clear(tree->root, tree->destructor);
    tree->root = NULL;
}

void rbtree_destructor(rbtree *tree) {
    rbtree_clear(tree);
    free(tree);
}
