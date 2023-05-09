#include "list.h"

list *list_constructor(size_t smemb) {
    list *l = malloc(sizeof *l);
    
    l->smemb = smemb;

    l->head = NULL;
    l->tail = NULL;

    return l;
}

void list_destructor(list *l) {
    dlnode_clear_fwd(l->head);
    dlnode_destructor(l->head);

    free(l);
}
