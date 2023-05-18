#include <stdlib.h>

#include "csci/cell.h"

#include "csci/csrc_matrix_iterator.h"

static const double __ZERO = 0;

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

Cell *__iterator_forward_row(CsrcMatrixIterator *self) {
    if (self->curr->nextCol == NULL)
        if (self->curr->row + 1 == csrc_matrix_shape_n(self->matrix))
            return NULL;
        else
            return csrc_matrix_get_row(self->matrix, self->curr->row + 1);
    else
        return self->curr->nextCol;
}

Cell *__iterator_forward_col(CsrcMatrixIterator *self) {
    if (self->curr->nextRow == NULL)
        if (self->curr->col + 1 == csrc_matrix_shape_m(self->matrix))
            return NULL;
        else
            return csrc_matrix_get_col(self->matrix, self->curr->col + 1);
    else
        return self->curr->nextRow;
}

CsrcMatrixIterator *csrc_matrix_iterator_begin(CsrcMatrix *mat) {
    CsrcMatrixIterator *iterator =
        (CsrcMatrixIterator *)malloc(sizeof(CsrcMatrixIterator));

    iterator->matrix = mat;
    iterator->row = 0;
    iterator->col = 0;

    iterator->curr = NULL;

    return iterator;
}

size_t csrc_matrix_iterator_get_i(CsrcMatrixIterator *self) {
    return self->row;
}

size_t csrc_matrix_iterator_get_j(CsrcMatrixIterator *self) {
    return self->col;
}

const double *csrc_matrix_iterator_forward_row_dense(CsrcMatrixIterator *self) {
    __iterator_begin_row(self);

    if (self->row == csrc_matrix_shape_n(self->matrix) - 1 &&
        self->col == csrc_matrix_shape_m(self->matrix) - 1)
        return NULL;

    const double *val = self->curr == NULL || self->curr->row != self->row ||
                          self->curr->col != self->col
                      ? &__ZERO
                      : &self->curr->data;

    self->col++;
    if (self->col % csrc_matrix_shape_m(self->matrix) == 0) {
        self->col = 0;
        self->row++;
    }

    if (self->curr == NULL || self->curr->col > self->col ||
        self->curr->row > self->row)
        return val;

    self->curr = __iterator_forward_row(self);

    return val;
}

Cell *csrc_matrix_iterator_forward_row_sparse(CsrcMatrixIterator *self) {
    __iterator_begin_row(self);

    if (!self->curr)
        return NULL;

    Cell *c = self->curr;

    self->col = self->curr->col;
    self->row = self->curr->row;

    self->curr = __iterator_forward_row(self);

    return c;
}

Cell *csrc_matrix_iterator_forward_column_sparse(CsrcMatrixIterator *self) {
    __iterator_begin_col(self);

    if (!self->curr)
        return NULL;

    Cell *c = self->curr;

    self->col = self->curr->col;
    self->row = self->curr->row;

    self->curr = __iterator_forward_col(self);

    return c;
}

void csrv_matrix_iterator_destructor(CsrcMatrixIterator *self) {
    free(self);    
}
