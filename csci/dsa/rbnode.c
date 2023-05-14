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

rbnode *rbnode_rotateleft(rbnode *root) {
    if (root == NULL)
        return root;

    /*
     *    r       |       x
     *      \     |     /
     *        x   |   r
     *      /     |     \
     *    y       |       y
     */

    rbnode *x = root->right;
    rbnode *y = x->left;

    x->left = root;
    x->parent = root->parent;
    root->parent = x;

    root->right = y;
    if (y != NULL)
        y->parent = root;

    return x;
}

rbnode *rbnode_rotateright(rbnode *root) {
    if (root == NULL)
        return root;

    /*
     *        r   |   y
     *      /     |     \
     *    y       |       r
     *      \     |     /
     *        x   |   x
     */

    rbnode *y = root->left;
    rbnode *x = y->right;

    y->right = root;
    y->parent = root->parent;
    root->parent = y;

    root->left = x;
    if (x != NULL)
        x->parent = root;

    return y;
}

rbnode *rbnode_rotateleftright(rbnode *root) {
    if (root == NULL)
        return root;

    /*
     *        r   |
     *      /     |       x
     *    y       |     /   \
     *      \     |   y       r
     *        x   |
     */

    rbnode_rotateleft(root->left);
    return rbnode_rotateright(root);
}

rbnode *rbnode_rotaterightleft(rbnode *root) {
    if (root == NULL)
        return root;

    /*
     *        r   |
     *      /     |       x
     *    y       |     /   \
     *      \     |   r       y
     *        x   |
     */

    rbnode_rotateright(root->right);
    return rbnode_rotateleft(root);
}

void *rbnode_iterator_begin(rbnode *root) {
    while (root->left != NULL)
        root = root->left;

    return root;
}

void *rbnode_iterator_forward(void **saveptr) {
    rbnode *curr = *saveptr;
    if (curr == NULL)
        return NULL;

    void *val = curr->key;

    if (curr->right != NULL) {
        curr = curr->right;
        while (curr->left != NULL)
            curr = curr->left;
    } else {
        while (curr->parent != NULL && curr == curr->parent->right)
            curr = curr->parent;
        curr = curr->parent;
    }

    *saveptr = curr;
    return val;
}

void *rbnode_iterator_reverse(void **saveptr) {
    rbnode *curr = *saveptr;
    if (curr == NULL)
        return NULL;

    void *val = curr->key;

    if (curr->left != NULL) {
        curr = curr->left;
        while (curr->right != NULL)
            curr = curr->right;
    } else {
        while (curr->parent != NULL && curr == curr->parent->left)
            curr = curr->parent;

        curr = curr->parent;
    }

    *saveptr = curr;
    return val;
}

void *rbnode_iterator_end(rbnode *root) {
    while (root->right != NULL)
        root = root->right;

    return root;
}

void rbnode_clear(rbnode *root, destruct_fn destructor) {
    if (root == NULL)
        return;

    rbnode_clear(root->left, destructor);
    rbnode_destructor(root->left, destructor);
    root->left = NULL;

    rbnode_clear(root->right, destructor);
    rbnode_destructor(root->right, destructor);
    root->right = NULL;
}

void rbnode_destructor(rbnode *node, destruct_fn destructor) {
    if (destructor != NULL)
        destructor(node->key);

    free(node);
}
