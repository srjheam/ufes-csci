#ifndef _LIST_H_
#define _LIST_H_

#include "common.h"
#include "dlnode.h"

typedef struct list {
    dlnode *head;
    dlnode *tail;

    size_t smemb;
} list;

list *list_constructor(size_t smemb);

void list_destructor(list *l);

#endif
