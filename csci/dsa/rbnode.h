#ifndef _RBNODE_H_
#define _RBNODE_H_

#include "common.h"

enum color_t { BLACK, RED };

typedef struct rbnode {
    void *key;

    struct rbnode *parent;
    struct rbnode *left;
    struct rbnode *right;

    enum color_t color;
} rbnode;

rbnode *rbnode_constructor(void *key, rbnode *parent, rbnode *left,
                           rbnode *right, enum color_t color);

rbnode *rbnode_rotateleft(rbnode *root);

rbnode *rbnode_rotateright(rbnode *root);

rbnode *rbnode_rotateleftright(rbnode *root);

rbnode *rbnode_rotaterightleft(rbnode *root);

void *rbnode_iterator_begin(rbnode *root);

void *rbnode_iterator_next(void **saveptr);

bool rbnode_iterator_has_next(void **saveptr);

void rbnode_clear(rbnode *root, destruct_fn destructor);

void rbnode_destructor(rbnode *node, destruct_fn destructor);

#endif
