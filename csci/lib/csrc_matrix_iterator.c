#include <stdlib.h>

#include "csci/cell.h"

#include "csci/csrc_matrix_iterator.h"

static const double __ZERO = 0;

struct CsrcMatrixIterator {
    CsrcMatrix *matrix;
    size_t nrow;
    size_t ncol;
    Cell *next;
};

void __iterator_begin_row(CsrcMatrixIterator *self) {
    if (self->nrow != 0 || self->ncol != 0)
        return;

    Cell *curr = NULL;
    for (size_t i = 0; !curr && i < csrc_matrix_shape_n(self->matrix); i++)
        curr = csrc_matrix_get_row(self->matrix, i);

    self->next = curr;
}

void __iterator_begin_col(CsrcMatrixIterator *self) {
    if (self->nrow != 0 || self->ncol != 0)
        return;

    Cell *curr = NULL;
    for (size_t j = 0; !curr && j < csrc_matrix_shape_m(self->matrix); j++)
        curr = csrc_matrix_get_col(self->matrix, j);

    self->next = curr;
}

Cell *__iterator_forward_row(CsrcMatrixIterator *self) {
    if (self->next->nextCol == NULL) {
        Cell *curr = NULL;
        for (size_t i = self->next->row + 1;
             !curr && i < csrc_matrix_shape_n(self->matrix); i++)
            curr = csrc_matrix_get_row(self->matrix, i);

        return curr;
    } else
        return self->next->nextCol;
}

Cell *__iterator_forward_col(CsrcMatrixIterator *self) {
    if (self->next->nextRow == NULL) {
        Cell *curr = NULL;
        for (size_t j = self->next->col + 1; !curr && j < csrc_matrix_shape_m(self->matrix); j++)
            curr = csrc_matrix_get_col(self->matrix, j);

        return curr;
    } else
        return self->next->nextRow;
}

CsrcMatrixIterator *csrc_matrix_iterator_begin(CsrcMatrix *mat) {
    CsrcMatrixIterator *iterator =
        (CsrcMatrixIterator *)malloc(sizeof(CsrcMatrixIterator));

    iterator->matrix = mat;
    iterator->nrow = 0;
    iterator->ncol = 0;

    iterator->next = NULL;

    return iterator;
}

size_t csrc_matrix_iterator_get_i(CsrcMatrixIterator *self) {
    if (self->ncol == 0)
        return self->nrow - 1;
    else
        return self->nrow;
}

size_t csrc_matrix_iterator_get_j(CsrcMatrixIterator *self) {
    size_t shape_m = csrc_matrix_shape_m(self->matrix);
    return (shape_m + self->ncol - 1) % shape_m;
}

const double *csrc_matrix_iterator_forward_row_dense(CsrcMatrixIterator *self) {
    __iterator_begin_row(self);

    if (self->nrow == csrc_matrix_shape_n(self->matrix))
        return NULL;

    const double *val = self->next == NULL || self->next->row != self->nrow ||
                                self->next->col != self->ncol
                            ? &__ZERO
                            : &self->next->data;

    self->ncol++;
    if (self->ncol % csrc_matrix_shape_m(self->matrix) == 0) {
        self->ncol = 0;
        self->nrow++;
    }

    if (self->next == NULL || self->next->col > self->ncol ||
        self->next->row > self->nrow)
        return val;

    self->next = __iterator_forward_row(self);

    return val;
}

Cell *csrc_matrix_iterator_forward_row_sparse(CsrcMatrixIterator *self) {
    __iterator_begin_row(self);

    if (!self->next)
        return NULL;

    Cell *c = self->next;

    self->ncol = (self->next->col + 1) % csrc_matrix_shape_m(self->matrix);
    if (self->ncol == 0)
        self->nrow++;

    self->next = __iterator_forward_row(self);

    return c;
}

Cell *csrc_matrix_iterator_forward_column_sparse(CsrcMatrixIterator *self) {
    __iterator_begin_col(self);

    if (!self->next)
        return NULL;

    Cell *c = self->next;

    self->nrow = (self->next->row + 1) % csrc_matrix_shape_n(self->matrix);
    if (self->nrow == 0)
        self->ncol++;

    self->next = __iterator_forward_col(self);

    return c;
}

void csrv_matrix_iterator_destructor(CsrcMatrixIterator *self) { free(self); }
