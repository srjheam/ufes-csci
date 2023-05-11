#include "rbtree.h"

rbtree *rbtree_constructor(size_t smemb, compar_fn compar) {
    rbtree *tree = malloc(sizeof *tree);

    tree->smemb = smemb;

    tree->compar = compar;

    tree->root = NULL;

    return tree;
}

void rbtree_insert(rbtree *tree, void *key) {
    if (tree->root == NULL) {
        tree->root =
            rbnode_constructor(tree->smemb, key, NULL, NULL, NULL, BLACK);
        return;
    }

    rbnode *root = tree->root;
    do {
        int cmp = tree->compar(key, root);
        if (cmp > 0) {
            if (root->right == NULL)
                break;
        } else if (root->left == NULL)
            break;

        root = cmp > 0 ? root->right : root->left;
    } while (root != NULL);

    rbnode *nnode =
        rbnode_constructor(tree->smemb, root, NULL, NULL, NULL, RED);

    int cmp = tree->compar(key, root);
    if (cmp > 0)
        root->right = nnode;
    else
        root->left = nnode;

    // maintain
    while (nnode->parent->color == RED) {
        rbnode *parent = nnode->parent;
        rbnode *grandpa = parent->parent;
        if (parent == grandpa->left) {
            if (grandpa->right != NULL && grandpa->right->color == RED) {
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

void *rbtree_lookup(rbtree *tree, void *key) {
    rbnode *curr = tree->root;
    while (curr != NULL) {
        int cmp = tree->compar(&key, &curr->key);
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
