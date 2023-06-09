#include <assert.h>
#include <stdio.h>

#include "dsa/exceptions.h"

#include "csci/csrc_matrix_iterator.h"

#include "csci/csrc_matrix.h"

struct CsrcMatrix {
    size_t shape_n;
    size_t shape_m;

    Index *rows;
    Index *cols;
};

void __csrc_matrix_set_addfix_cols(CsrcMatrix *self, Cell *cell) {
    Head *col = index_lookup(self->cols, cell->col);
    if (!col) {
        col = index_add(self->cols, cell->col);
        col->head = cell;

        return;
    }

    Cell *currRow = head_first(col);
    while (currRow->nextRow && currRow->nextRow->row <= cell->row)
        currRow = currRow->nextRow;

    if (currRow->row > cell->row) {
        cell->nextRow = currRow;
        cell->prevRow = NULL;

        currRow->prevRow = cell;

        col->head = cell;
    } else {
        cell->prevRow = currRow;
        cell->nextRow = currRow->nextRow;

        currRow->nextRow = cell;
    }
}

Index **_csrc_matrix_rows(CsrcMatrix *self) { return &self->rows; }

Index **_csrc_matrix_cols(CsrcMatrix *self) { return &self->cols; }

Cell *_csrc_matrix_get_r(CsrcMatrix *self, size_t i, size_t j) {
    if (i >= self->shape_n || j >= self->shape_m)
        exception_throw_index("csrc_matrix_get");

    Head *row = index_lookup(self->rows, i);
    if (!row)
        return NULL;

    Cell *currCol = head_first(row);

    assert(currCol != NULL);

    while (currCol && currCol->col < j)
        currCol = currCol->nextCol;

    if (!currCol || currCol->col > j)
        return NULL;

    return currCol;
}

CsrcMatrix *csrc_matrix_constructor_z(size_t n, size_t m) {
    CsrcMatrix *self = malloc(sizeof *self);

    self->shape_n = n;
    self->shape_m = m;

    self->rows = index_constructor();
    self->cols = index_constructor();

    return self;
}

CsrcMatrix *csrc_matrix_indentity(size_t n) {
    CsrcMatrix *id = csrc_matrix_constructor_z(n, n);

    for (size_t i = 0; i < n; i++)
        csrc_matrix_set(id, i, i, 1);

    return id;
}

double csrc_matrix_get(CsrcMatrix *self, size_t i, size_t j) {
    Cell *cell = _csrc_matrix_get_r(self, i, j);
    return cell ? cell->data : 0;
}

Cell *csrc_matrix_get_row(CsrcMatrix *self, size_t i) {
    if (i >= self->shape_n)
        exception_throw_index("csrc_matrix_get_row");

    Head *row = index_lookup(self->rows, i);
    if (!row)
        return NULL;

    return head_first(row);
}

Cell *csrc_matrix_get_col(CsrcMatrix *self, size_t j) {
    if (j >= self->shape_m)
        exception_throw_index("csrc_matrix_get_col");

    Head *col = index_lookup(self->cols, j);
    if (!col)
        return NULL;

    return head_first(col);
}

size_t csrc_matrix_shape_n(CsrcMatrix *self) { return self->shape_n; }

size_t csrc_matrix_shape_m(CsrcMatrix *self) { return self->shape_m; }

void csrc_matrix_set(CsrcMatrix *self, size_t i, size_t j, double value) {
    if (i >= self->shape_n || j >= self->shape_m)
        exception_throw_index("csrc_matrix_set");

    Head *row = index_lookup(self->rows, i);
    if (!row) {
        if (value == 0)
            return;

        row = index_add(self->rows, i);
    }

    Cell *currCol = head_first(row);
    if (!currCol) {
        row->head = cell_constructor(i, j, value);

        __csrc_matrix_set_addfix_cols(self, row->head);

        return;
    }

    while (currCol->nextCol && currCol->nextCol->col <= j)
        currCol = currCol->nextCol;

    if (currCol->col == j) {
        if (value == 0) {
            cell_remove(currCol);

            // update row head
            Cell *firstCol = head_first(row);
            if (firstCol == currCol)
                row->head = firstCol->nextCol;

            // remove row
            firstCol = head_first(row);
            if (!firstCol)
                index_remove(self->rows, i);

            Head *col = index_lookup(self->cols, j);
            if (!col)
                return;

            // update col head
            Cell *firstRow = head_first(col);
            if (firstRow == currCol)
                col->head = firstRow->nextRow;

            // remove col
            firstRow = head_first(col);
            if (!firstRow)
                index_remove(self->cols, j);

            cell_destructor(currCol);

            return;
        }

        currCol->data = value;
    } else {
        if (value == 0)
            return;

        Cell *ncell = cell_constructor(i, j, value);

        if (currCol->col > j) {
            ncell->nextCol = currCol;
            ncell->prevCol = currCol->prevCol;

            currCol->prevCol = ncell;

            if (ncell->prevCol)
                ncell->prevCol->nextCol = ncell;
            else
                row->head = ncell;
        } else {
            ncell->prevCol = currCol;
            ncell->nextCol = currCol->nextCol;

            currCol->nextCol = ncell;
        }

        __csrc_matrix_set_addfix_cols(self, ncell);
    }
}

int csrc_matrix_compar(CsrcMatrix *self, CsrcMatrix *b) {
    if (self->shape_n != b->shape_n || self->shape_m != b->shape_m)
        return 0;

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    CsrcMatrixIterator *itb = csrc_matrix_iterator_begin(b);

    Cell *curr = csrc_matrix_iterator_forward_row_sparse(it);
    Cell *currb = csrc_matrix_iterator_forward_row_sparse(itb);

    while (curr && currb) {
        if (curr->row != currb->row || curr->col != currb->col ||
            curr->data != currb->data) {
            csrv_matrix_iterator_destructor(it);
            csrv_matrix_iterator_destructor(itb);

            return 0;
        }

        curr = csrc_matrix_iterator_forward_row_sparse(it);
        currb = csrc_matrix_iterator_forward_row_sparse(itb);
    }

    csrv_matrix_iterator_destructor(it);
    csrv_matrix_iterator_destructor(itb);

    if (curr || currb)
        return 0;

    return 1;
}

CsrcMatrix *csrc_matrix_copy(CsrcMatrix *self) {
    CsrcMatrix *nmat = csrc_matrix_constructor_z(self->shape_n, self->shape_m);

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it))
        csrc_matrix_set(nmat, curr->row, curr->col, curr->data);

    csrv_matrix_iterator_destructor(it);

    return nmat;
}

void csrc_matrix_clear(CsrcMatrix *self) {
    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it))
        cell_destructor(curr);

    csrv_matrix_iterator_destructor(it);
}

void csrc_matrix_destructor(CsrcMatrix *self) {
    csrc_matrix_clear(self);

    index_destructor(self->rows);
    index_destructor(self->cols);

    free(self);
}
