#ifndef _CSCI_HEAD_H_
#define _CSCI_HEAD_H_

typedef struct {
    size_t i;
    list *v;
} Head;

int head_compar(const Head *a, const Head *b);

#endif
