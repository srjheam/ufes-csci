#include "dsa/rbtree.h"

rbnode *__rbtree_lookup_node(rbtree *tree, void *key) {
    rbnode *curr = tree->root;
    while (curr != NULL) {
        int cmp = tree->comparer(key, curr->key);
        if (cmp == 0)
            return curr;

        if (curr->left == NULL || curr->right == NULL) {
            curr = curr->left == NULL ? curr->right : curr->left;
            continue;
        }

        curr = cmp < 0 ? curr->left : curr->right;
    }

    return NULL;
}

void *__rbtree_replace(rbtree *tree, rbnode *node, rbnode *x) {
    if (node->parent == NULL) {
        tree->root = x;
    } else if (node->parent->left == node) {
        node->parent->left = x;
    } else {
        node->parent->right = x;
    }

    if (x != NULL)
        x->parent = node->parent;

    return node->key;
}

rbnode *__rbtree_fixup_insert(rbnode *node) {
    while (node->parent != NULL && node->parent->color == RED) {
        rbnode *grandparent = node->parent->parent;
        rbnode *uncle = grandparent->left == node->parent ? grandparent->right
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

// TODO:
//     Test this function complieance with the red-black tree properties
void __rbtree_fixup_remove(rbnode *x) {
    while (x != NULL && x->parent != NULL && x->color == BLACK) {
        rbnode *sibling = x->parent->left == x ? x->parent->right
                                               : x->parent->left;

        if (sibling->color == RED) {
            sibling->color = BLACK;
            x->parent->color = RED;

            if (x->parent->left == x) {
                rbnode *y = rbnode_rotateleft(x->parent);

                sibling = y->right;
            } else {
                rbnode *y = rbnode_rotateright(x->parent);

                sibling = y->left;
            }
        }

        if ((sibling->left == NULL || sibling->left->color == BLACK) &&
            (sibling->right == NULL || sibling->right->color == BLACK)) {
            sibling->color = RED;
            x = x->parent;
            continue;
        }

        if (x->parent->left == x) {
            if (sibling->right == NULL || sibling->right->color == BLACK) {
                sibling->left->color = BLACK;
                sibling->color = RED;

                rbnode *y = rbnode_rotateright(sibling);

                sibling = y->left;
            }

            sibling->color = x->parent->color;
            x->parent->color = BLACK;
            sibling->right->color = BLACK;

            rbnode *y = rbnode_rotateleft(x->parent);

            x = y;
            continue;
        }

        if (sibling->left == NULL || sibling->left->color == BLACK) {
            sibling->right->color = BLACK;
            sibling->color = RED;

            rbnode *y = rbnode_rotateleft(sibling);

            sibling = y->right;
        }

        sibling->color = x->parent->color;
        x->parent->color = BLACK;
        sibling->left->color = BLACK;

        rbnode *y = rbnode_rotateright(x->parent);

        x = y;
    }

    if (x != NULL)
        x->color = BLACK;
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

    tree->root = __rbtree_fixup_insert(node);
}

void *rbtree_remove(rbtree *tree, void *key) {
    rbnode *node = __rbtree_lookup_node(tree, key);
    if (node == NULL)
        return NULL;

    enum color_t color = node->color;

    rbnode *x = NULL;
    if (node->left == NULL) {
        x = node->right;

        __rbtree_replace(tree, node, x);
    } else if (node->right == NULL) {
        x = node->left;

        __rbtree_replace(tree, node, x);
    } else {
        rbnode *y = node->right;
        while (y->left != NULL)
            y = y->left;

        color = y->color;
        x = y->right;

        if (y->parent == node) {
            if (x != NULL)
                x->parent = y;
        } else
            __rbtree_replace(tree, y, x);

        __rbtree_replace(tree, node, y);
        y->color = color;

        x = y;
    }

    if (color == BLACK)
        __rbtree_fixup_remove(x);

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void *rbtree_iterator_begin(rbtree *tree) {
    return rbnode_iterator_begin(tree->root);
}

void *rbtree_iterator_forward(void **saveptr) {
    return rbnode_iterator_forward(saveptr);
}

void *rbtree_iterator_reverse(void **saveptr) {
    return rbnode_iterator_reverse(saveptr);
}

void *rbtree_iterator_end(rbtree *tree) {
    return rbnode_iterator_end(tree->root);
}

void rbtree_clear(rbtree *tree) {
    rbnode_clear(tree->root, tree->destructor);
    rbnode_destructor(tree->root, tree->destructor);
    tree->root = NULL;
}

void rbtree_destructor(rbtree *tree) {
    rbtree_clear(tree);
    free(tree);
}
