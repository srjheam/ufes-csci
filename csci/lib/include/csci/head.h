#ifndef _CSCI_HEAD_H_
#define _CSCI_HEAD_H_

#include "cell.h"

typedef struct {
    size_t i;
    Cell *head;
} Head;

size_t head_index(const Head *head);

Cell *head_first(const Head *head);

int head_compar(const Head *a, const Head *b);

#endif
