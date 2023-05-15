#ifndef _DLNODE_H_
#define _DLNODE_H_

#include "dsa/common.h"

typedef struct dlnode {
    byte *data;

    struct dlnode *next;
    struct dlnode *prev;
} dlnode;

dlnode *dlnode_constructor(void *data, dlnode *next, dlnode *prev);

void dlnode_clear_fwd(dlnode *node);

void dlnode_destructor(dlnode *node);

#endif
