#include "dsa/list.h"

list *list_constructor(compar_fn compar, copy_fn copy, destruct_fn destruct) {
    list *l = malloc(sizeof *l);

    l->compar = compar;
    l->copy = copy;
    l->destruct = destruct;

    l->head = NULL;
    l->tail = NULL;

    return l;
}

void list_destructor(list *l) {
    dlnode_clear_fwd(l->head);
    dlnode_destructor(l->head);

    free(l);
}
