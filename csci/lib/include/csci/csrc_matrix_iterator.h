#ifndef _CSCI_CSRC_MATRIX_ITERATOR_H_
#define _CSCI_CSRC_MATRIX_ITERATOR_H_

#include "csci/csrc_matrix.h"

typedef struct CsrcMatrixIterator CsrcMatrixIterator;

CsrcMatrixIterator *csrc_matrix_iterator_begin(CsrcMatrix *self);

double *csrc_matrix_iterator_forward(CsrcMatrixIterator *self);

void csrv_matrix_iterator_destructor(CsrcMatrixIterator *self);

#endif
