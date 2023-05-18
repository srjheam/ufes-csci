#ifndef _CSCI_CSRC_MATRIX_ITERATOR_H_
#define _CSCI_CSRC_MATRIX_ITERATOR_H_

#include "csci/csrc_matrix.h"

typedef struct CsrcMatrixIterator CsrcMatrixIterator;

CsrcMatrixIterator *csrc_matrix_iterator_begin(CsrcMatrix *mat);

size_t csrc_matrix_iterator_get_i(CsrcMatrixIterator *self);

size_t csrc_matrix_iterator_get_j(CsrcMatrixIterator *self);

const double *csrc_matrix_iterator_forward_row_dense(CsrcMatrixIterator *self);

Cell *csrc_matrix_iterator_forward_row_sparse(CsrcMatrixIterator *self);

Cell *csrc_matrix_iterator_forward_column_sparse(CsrcMatrixIterator *self);

void csrv_matrix_iterator_destructor(CsrcMatrixIterator *self);

#endif
