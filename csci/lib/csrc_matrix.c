#include "assert.h"

#include "dsa/exceptions.h"

#include "csci/index.h"

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

CsrcMatrix *csrc_matrix_constructor_z(int n, int m) {
    CsrcMatrix *self = malloc(sizeof *self);

    self->shape_n = n;
    self->shape_m = m;

    self->rows = index_constructor();
    self->cols = index_constructor();

    return self;
}

double csrc_matrix_get(CsrcMatrix *self, int i, int j) {
    if (i < 0 || i >= self->shape_n || j < 0 || j >= self->shape_m)
        exception_throw_index("csrc_matrix_get");

    Head *row = index_lookup(self->rows, i);
    if (!row)
        return 0;

    Cell *currCol = head_first(row);

    assert(currCol != NULL);

    while (currCol && currCol->col < j)
        currCol = currCol->nextCol;

    if (!currCol || currCol->col > j)
        return 0;

    return currCol->data;
}

Cell *csrc_matrix_get_row(CsrcMatrix *self, int i) {
    if (i < 0 || i >= self->shape_n)
        exception_throw_index("csrc_matrix_get_row");

    Head *row = index_lookup(self->rows, i);
    if (!row)
        return NULL;

    return head_first(row);
}

Cell *csrc_matrix_get_col(CsrcMatrix *self, int j) {
    if (j < 0 || j >= self->shape_m)
        exception_throw_index("csrc_matrix_get_col");

    Head *col = index_lookup(self->cols, j);
    if (!col)
        return NULL;

    return head_first(col);
}

size_t csrc_matrix_shape_n(CsrcMatrix *self) { return self->shape_n; }

size_t csrc_matrix_shape_m(CsrcMatrix *self) { return self->shape_m; }

void csrc_matrix_set(CsrcMatrix *self, int i, int j, double value) {
    if (i < 0 || i >= self->shape_n || j < 0 || j >= self->shape_m)
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

    if (currCol->col < j && value == 0)
        return;

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
                col->head = firstRow->nextCol;

            // remove col
            firstRow = head_first(col);
            if (!firstRow)
                index_remove(self->cols, j);

            return;
        }

        currCol->data = value;
    } else {
        Cell *ncell = cell_constructor(i, j, value);

        ncell->prevCol = currCol;
        ncell->nextCol = currCol->nextCol;

        currCol->nextCol = ncell;

        __csrc_matrix_set_addfix_cols(self, ncell);
    }
}

void csrc_matrix_print_sparse(CsrcMatrix *self);

void csrc_matrix_clear(CsrcMatrix *self);

void csrc_matrix_destructor(CsrcMatrix *self);
