#include "dlnode.h"

dlnode *dlnode_constructor(size_t smemb, void *data, dlnode *next,
                           dlnode *prev) {
    dlnode *nnode = malloc(sizeof *nnode);

    nnode->smemb = smemb;

    nnode->data = malloc(smemb);
    memcpy(nnode->data, data, smemb);

    nnode->next = next;
    nnode->prev = prev;

    return nnode;
}

void dlnode_clear_fwd(dlnode *node) {
    if (node == NULL)
        return;

    dlnode_clear_fwd(node->next);
    dlnode_destructor(node->next);
    node->next = NULL;
}

void dlnode_destructor(dlnode *node) {
    free(node->data);

    free(node);
}
