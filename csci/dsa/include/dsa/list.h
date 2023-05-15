#ifndef _LIST_H_
#define _LIST_H_

#include "dsa/common.h"
#include "dsa/dlnode.h"

typedef struct list {
    dlnode *head;
    dlnode *tail;

    compar_fn compar;
    copy_fn copy;
    destruct_fn destruct;
} list;

list *list_constructor(compar_fn compar, copy_fn copy, destruct_fn destruct);

void list_destructor(list *l);

#endif
