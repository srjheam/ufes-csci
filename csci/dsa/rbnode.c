#include "rbnode.h"

rbnode *rbnode_constructor(void *key, rbnode *parent, rbnode *left,
                           rbnode *right, enum color_t color) {
    rbnode *node = malloc(sizeof *node);

    node->key = key;

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
    } else if (root->parent->left == root) {
        root->parent->left = oright;
        oright->parent = root->parent;
    } else {
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
    } else if (root->parent->right == root) {
        root->parent->right = oleft;
        oleft->parent = root->parent;
    } else {
        root->parent->right = oleft;
        oleft->parent = root->parent;
    }

    root->parent = oleft;
}

void rbnode_rotateleftright(rbnode *root) {
    if (root == NULL)
        return;

    rbnode_rotateleft(root->left);
    rbnode_rotateright(root);
}

void rbnode_rotaterightleft(rbnode *root) {
    if (root == NULL)
        return;

    rbnode_rotateright(root->right);
    rbnode_rotateleft(root);
}

void rbnode_clear(rbnode *root, destruct_fn destructor) {
    if (root == NULL)
        return;

    rbnode_clear(root->left, destructor);
    rbnode_clear(root->right, destructor);

    rbnode_destructor(root, destructor);
}

void rbnode_destructor(rbnode *node, destruct_fn destructor) {
    if (destructor != NULL)
        destructor(node->key);

    free(node);
}
