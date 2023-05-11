#ifndef _DLNODE_H_
#define _DLNODE_H_

#include "common.h"

typedef struct dlnode {
    byte *data;

    struct dlnode *next;
    struct dlnode *prev;

    size_t smemb;
} dlnode;

dlnode *dlnode_constructor(size_t smemb, void *data, dlnode *next,
                           dlnode *prev);

void dlnode_clear_fwd(dlnode *node);

void dlnode_destructor(dlnode *node);

#endif
