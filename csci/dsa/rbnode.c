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

void *rbnode_setparent(rbnode *node, rbnode *nparent) {
    rbnode *sp = node->parent;
    node->parent = nparent;
    return sp;
}

void *rbnode_setleft(rbnode *node, rbnode *nleft) {
    rbnode *sl = node->right;
    node->left = nleft;
    return sl;
}

void *rbnode_setright(rbnode *node, rbnode *nright) {
    rbnode *sr = node->right;
    node->right = nright;
    return sr;
}

void rbnode_destructor(rbnode *node) {
    free(node->key);

    free(node);
}
