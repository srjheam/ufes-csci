#include "rbtree.h"

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

    rbnode *root = tree->root;
    do {
        int cmp = tree->comparer(key, root->key);
        if (cmp > 0) {
            if (root->right == NULL)
                break;
        } else if (root->left == NULL)
            break;

        root = cmp > 0 ? root->right : root->left;
    } while (1);

    rbnode *nnode = rbnode_constructor(key, root, NULL, NULL, RED);

    int cmp = tree->comparer(key, root->key);
    if (cmp > 0)
        root->right = nnode;
    else
        root->left = nnode;

    // maintain
    if (nnode->parent->color == BLACK)
        return;

    while (nnode->parent != NULL && nnode->parent->color == RED) {
        rbnode *parent = nnode->parent;
        rbnode *grandpa = parent->parent;
        if (parent == grandpa->left) {
            if (grandpa->right->color == RED) {
                grandpa->right->color = BLACK;
                grandpa->left->color = BLACK;
                grandpa->color = RED;

                nnode = grandpa;
            } else if (nnode == parent->right) {
                nnode = parent;

                rbnode_rotateleft(nnode);
            } else {
                parent->color = BLACK;
                grandpa->color = RED;

                rbnode_rotateright(grandpa);
            }
        } else {
            if (grandpa->left->color == RED) {
                grandpa->right->color = BLACK;
                grandpa->left->color = BLACK;
                grandpa->color = RED;

                nnode = grandpa;
            } else if (nnode == parent->left) {
                nnode = parent;

                rbnode_rotateright(nnode);

                parent->color = BLACK;
                grandpa->color = RED;

                rbnode_rotateleft(grandpa);
            }
        }
    }

    rbnode *curr = tree->root;
    while ((curr = curr->parent)) {
        tree->root = curr;
    }

    tree->root->color = BLACK;
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

void rbtree_clear(rbtree *tree) {
    rbnode_clear(tree->root, tree->destructor);
    tree->root = NULL;
}

void rbtree_destructor(rbtree *tree) {
    rbtree_clear(tree);
    free(tree);
}
