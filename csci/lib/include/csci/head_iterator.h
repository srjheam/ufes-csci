#ifndef _CSCI_HEAD_ITERATOR_H_
#define _CSCI_HEAD_ITERATOR_H_

#include "csci/head.h"

typedef struct HeadIterator HeadIterator;

HeadIterator *head_iterator_begin(Head *head, size_t shape);

const double *head_iterator_forward_row_sparse(HeadIterator *self);

HeadIterator *head_iterator_destructor(HeadIterator *self);

#endif
