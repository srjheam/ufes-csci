#ifndef _RBNODE_H_
#define _RBNODE_H_

#include "common.h"

enum color_t { BLACK, RED };

typedef struct rbnode {
    byte *key;

    struct rbnode *parent;
    struct rbnode *left;
    struct rbnode *right;

    enum color_t color;
} rbnode;

rbnode *rbnode_constructor(size_t smemb, void *key, rbnode *parent,
                           rbnode *left, rbnode *right, enum color_t color);

void rbnode_rotateleft(rbnode *root);

void rbnode_rotateright(rbnode *root);

void rbnode_rotateleftright(rbnode *root);

void rbnode_rotaterightleft(rbnode *root);

void rbnode_destructor(rbnode *node);

#endif
