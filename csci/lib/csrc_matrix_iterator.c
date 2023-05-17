#include <stdlib.h>

#include "csci/cell.h"

#include "csci/csrc_matrix_iterator.h"

struct CsrcMatrixIterator {
    CsrcMatrix *matrix;
    size_t row;
    size_t col;
    Cell *curr;
};

void __iterator_begin_row(CsrcMatrixIterator *self) {
    if (self->row != 0 || self->col != 0)
        return;

    Cell *curr = NULL;
    for (size_t i = 0; !curr && i < csrc_matrix_shape_n(self->matrix); i++)
        curr = csrc_matrix_get_row(self->matrix, i);

    self->curr = curr;
}

void __iterator_begin_col(CsrcMatrixIterator *self) {
    if (self->row != 0 || self->col != 0)
        return;

    Cell *curr = NULL;
    for (size_t j = 0; !curr && j < csrc_matrix_shape_m(self->matrix); j++)
        curr = csrc_matrix_get_col(self->matrix, j);

    self->curr = curr;
}

CsrcMatrixIterator *csrc_matrix_iterator_begin(CsrcMatrix *mat) {
    CsrcMatrixIterator *iterator =
        (CsrcMatrixIterator *)malloc(sizeof(CsrcMatrixIterator));

    iterator->matrix = mat;
    iterator->row = 0;
    iterator->col = 0;

    Cell *curr = NULL;

    return iterator;
}

size_t csrc_matrix_iterator_get_i(CsrcMatrixIterator *self) {
    return self->row;
}

size_t csrc_matrix_iterator_get_j(CsrcMatrixIterator *self) {
    return self->col;
}

double csrc_matrix_iterator_forward_row_dense(CsrcMatrixIterator *self) {
    __iterator_begin_row(self);

    double val = self->curr == NULL ? 0
                 : self->curr->row == self->row && self->curr->col == self->col
                     ? self->curr->data
                     : 0;
    
        
}

Cell *csrc_matrix_iterator_forward_row_sparse(CsrcMatrixIterator *self) {
    __iterator_begin_row(self);
}

Cell *csrc_matrix_iterator_forward_column_sparse(CsrcMatrixIterator *self) {
    __iterator_begin_col(self);
}

void csrv_matrix_iterator_destructor(CsrcMatrixIterator *self) {}
