#include "rbnode.h"

rbnode *rbnode_constructor(size_t smemb, void *key, rbnode *parent,
                           rbnode *left, rbnode *right, enum color_t color) {
    rbnode *node = malloc(sizeof *node);

    node->key = malloc(smemb);
    memcpy(node->key, key, smemb);

    node->parent = parent;

    node->left = left;
    node->right = right;

    node->color = color;

    return node;
}

void rbnode_rotateleft(rbnode *root) {
    if (root == NULL || root->right == NULL || root->right->left == NULL)
        return;

    rbnode *oright = root->right;

    root->right = oright->left;
    root->right->parent = root;
    oright->parent = NULL;

    if (root->parent == NULL) {
        oright->left = root;
    }
    else if (root->parent->left == root) {
        root->parent->left = oright;
        oright->parent = root->parent;
    }
    else {
        root->parent->right = oright;
        oright->parent = root->parent;
    }

    root->parent = oright;
}

void rbnode_rotateright(rbnode *root) {
    if (root == NULL || root->left == NULL || root->left->right == NULL)
        return;

    rbnode *oleft = root->left;

    root->left = oleft->right;
    root->left->parent = root;
    oleft->parent = NULL;

    if (root->parent == NULL) {
        oleft->right = root;
    }
    else if (root->parent->right == root) {
        root->parent->right = oleft;
        oleft->parent = root->parent;
    }
    else {
        root->parent->right = oleft;
        oleft->parent = root->parent;
    }

    root->parent = oleft;
}

void rbnode_destructor(rbnode *node) {
    free(node->key);

    free(node);
}
