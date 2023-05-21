#include "dsa/exceptions.h"

#include "csci/csrc_matrix_iterator.h"

#include "csci/csrc_matrix_oper.h"

CsrcMatrix *csrc_matrix_add(CsrcMatrix *self, CsrcMatrix *b) {
    size_t self_shape_n = csrc_matrix_shape_n(self);
    size_t self_shape_m = csrc_matrix_shape_m(self);

    size_t b_shape_n = csrc_matrix_shape_n(b);
    size_t b_shape_m = csrc_matrix_shape_m(b);

    if (self_shape_n != b_shape_n || self_shape_m != b_shape_m)
        exception_throw_argument("csrc_matrix_add");

    CsrcMatrix *result = csrc_matrix_copy(self);

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(b);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it)) {
        double self_val = csrc_matrix_get(self, curr->row, curr->col);
        csrc_matrix_set(result, curr->row, curr->col, self_val + curr->data);
    }

    csrv_matrix_iterator_destructor(it);

    return result;
}

CsrcMatrix *csrc_matrix_mul_scalar(CsrcMatrix *self, double scalar) {
    CsrcMatrix *result = csrc_matrix_copy(self);

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it))
        csrc_matrix_set(result, curr->row, curr->col, curr->data * scalar);

    csrv_matrix_iterator_destructor(it);

    return result;
}

CsrcMatrix *csrc_matrix_mul(CsrcMatrix *self, CsrcMatrix *b) {
    size_t self_shape_n = csrc_matrix_shape_n(self);
    size_t self_shape_m = csrc_matrix_shape_m(self);

    size_t b_shape_n = csrc_matrix_shape_n(b);
    size_t b_shape_m = csrc_matrix_shape_m(b);

    if (self_shape_m != b_shape_n)
        exception_throw_argument("csrc_matrix_mul");

    CsrcMatrix *result = csrc_matrix_constructor_z(self_shape_n, b_shape_m);

    // it could be faster if we iterate over the smaller matrix
    // but CsrcMatrix doesn't save the number of non-zero elements

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(b);
    for (Cell *currB = csrc_matrix_iterator_forward_row_sparse(it); currB;
         currB = csrc_matrix_iterator_forward_row_sparse(it))
        for (Cell *currSelf = csrc_matrix_get_col(self, currB->row); currSelf;
             currSelf = currSelf->nextRow) {
            double mult = currB->data * currSelf->data;

            double curr_val =
                csrc_matrix_get(result, currSelf->row, currB->col);
            csrc_matrix_set(result, currSelf->row, currB->col, curr_val + mult);
        }

    csrv_matrix_iterator_destructor(it);

    return result;
}

CsrcMatrix *csrc_matrix_dot(CsrcMatrix *self, CsrcMatrix *b) {
    size_t self_shape_n = csrc_matrix_shape_n(self);
    size_t self_shape_m = csrc_matrix_shape_m(self);

    size_t b_shape_n = csrc_matrix_shape_n(b);
    size_t b_shape_m = csrc_matrix_shape_m(b);

    if (self_shape_n != b_shape_n || self_shape_m != b_shape_m)
        exception_throw_argument("csrc_matrix_dot");

    CsrcMatrix *result = csrc_matrix_constructor_z(self_shape_n, self_shape_m);

    // it could be faster if we iterate over the smaller matrix
    // but CsrcMatrix doesn't save the number of non-zero elements

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(b);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it)) {
        double self_val = csrc_matrix_get(self, curr->row, curr->col);
        csrc_matrix_set(result, curr->row, curr->col, self_val * curr->data);
    }

    csrv_matrix_iterator_destructor(it);

    return result;
}

void __row_place_next(Cell *prev, Cell *next) {
    if (next->prevRow)
        next->prevRow->nextRow = next->nextRow;

    if (next->nextRow)
        next->nextRow->prevRow = next->prevRow;

    next->prevRow = prev;

    Cell *pn = prev->nextRow;

    prev->nextRow = next;
    if (pn)
        pn->prevRow = next;

    next->nextRow = pn;
}

void __row_place_before(Cell *next, Cell *prev) {
    if (prev->nextRow)
        prev->nextRow->prevRow = prev->prevRow;

    if (prev->prevRow)
        prev->prevRow->nextRow = prev->nextRow;

    prev->nextRow = next;

    Cell *pn = next->prevRow;

    next->prevRow = prev;
    if (pn)
        pn->nextRow = prev;

    prev->prevRow = pn;
}

CsrcMatrix *csrc_matrix_swap_rows(CsrcMatrix *self, size_t i1, size_t i2) {
    size_t self_shape_n = csrc_matrix_shape_n(self);

    if (i1 >= self_shape_n || i2 >= self_shape_n)
        exception_throw_argument("csrc_matrix_swap_rows");

    CsrcMatrix *result = csrc_matrix_copy(self);

    if (i1 == i2)
        return result;

    if (i1 > i2) {
        size_t tmp = i1;
        i1 = i2;
        i2 = tmp;
    }

    Cell *row1 = csrc_matrix_get_row(result, i1);
    Cell *row2 = csrc_matrix_get_row(result, i2);
    while (row1 || row2) {
        if (row1 && row2 && row1->col == row2->col) {
            if (i1 + 1 == i2) {
                row1->nextRow = row2->nextRow;
                if (row1->nextRow)
                    row1->nextRow->prevRow = row1;

                row1->prevRow = row2;

                row2->prevRow = row1->prevRow;
                if (row2->prevRow)
                    row2->prevRow->nextRow = row2;

                row2->nextRow = row1;
            } else {
                Cell *tmp = row1->nextRow;

                row1->nextRow = row2->nextRow;
                if (row1->nextRow)
                    row1->nextRow->prevRow = row1;

                row2->nextRow = tmp;
                row2->nextRow->prevRow = row2;

                tmp = row1->prevRow;

                row1->prevRow = row2->prevRow;
                row1->prevRow->nextRow = row1;

                row2->prevRow = tmp;
                if (row2->prevRow)
                    row2->prevRow->nextRow = row2;
            }

            row1->row = i2;
            row1 = row1->nextCol;

            row2->row = i1;
            row2 = row2->nextCol;
        } else if ((row1 && row2 && row1->col < row2->col) || (row1 && !row2)) {
            Cell *prev = row1;
            while (prev->nextRow && prev->nextRow->row < i2)
                prev = prev->nextRow;

            __row_place_next(prev, row1);

            row1->row = i2;
            row1 = row1->nextCol;
        } else {
            Cell *next = row2;
            while (next->prevRow && next->prevRow->row > i1)
                next = next->prevRow;

            __row_place_before(next, row2);

            row2->row = i1;
            row2 = row2->nextCol;
        }
    }

    if (i1 == 0) {
        Index **cols = _csrc_matrix_cols(result);
        Cell *row = csrc_matrix_get_row(result, i2);
        for (size_t j = 0; j < csrc_matrix_shape_m(result); j++) {
            Head *currCol = index_lookup(*cols, j);
            if (!currCol)
                continue;

            while (row && row->col < j)
                row = row->nextCol;

            if (row && row->col == j)
                currCol->head = row;
            else if (currCol->head->row == i2) {
                Cell *h = currCol->head;
                while (h->prevRow)
                    h = h->prevRow;

                currCol->head = h;
            }
        }
    }

    Index *rows = *_csrc_matrix_rows(result);
    Head *h1 = index_lookup(rows, i1);
    Head *h2 = index_lookup(rows, i2);
    Cell *tmp = h1->head;
    h1->head = h2->head;
    h2->head = tmp;

    return result;
}

void __col_place_next(Cell *prev, Cell *next) {
    if (next->prevCol)
        next->prevCol->nextCol = next->nextCol;

    if (next->nextCol)
        next->nextCol->prevCol = next->prevCol;

    next->prevCol = prev;

    Cell *pn = prev->nextCol;

    prev->nextCol = next;
    if (pn)
        pn->prevCol = next;

    next->nextCol = pn;
}

void __col_place_before(Cell *next, Cell *prev) {
    if (prev->nextCol)
        prev->nextCol->prevCol = prev->prevCol;

    if (prev->prevCol)
        prev->prevCol->nextCol = prev->nextCol;

    prev->nextCol = next;

    Cell *pn = next->prevCol;

    next->prevCol = prev;
    if (pn)
        pn->nextCol = prev;

    prev->prevCol = pn;
}

CsrcMatrix *csrc_matrix_swap_cols(CsrcMatrix *self, size_t j1, size_t j2) {
    size_t self_shape_m = csrc_matrix_shape_m(self);

    if (j1 >= self_shape_m || j2 >= self_shape_m)
        exception_throw_argument("csrc_matrix_swap_cols");

    CsrcMatrix *result = csrc_matrix_copy(self);

    if (j1 == j2)
        return result;

    if (j1 > j2) {
        size_t tmp = j1;
        j1 = j2;
        j2 = tmp;
    }

    Cell *col1 = csrc_matrix_get_col(result, j1);
    Cell *col2 = csrc_matrix_get_col(result, j2);
    while (col1 || col2) {
        if (col1 && col2 && col1->row == col2->row) {
            if (j1 + 1 == j2) {
                col1->nextCol = col2->nextCol;
                if (col1->nextCol)
                    col1->nextCol->prevCol = col1;

                col1->prevCol = col2;

                col2->prevCol = col1->prevCol;
                if (col2->prevCol)
                    col2->prevCol->nextCol = col2;

                col2->nextCol = col1;
            } else {
                Cell *tmp = col1->nextCol;

                col1->nextCol = col2->nextCol;
                if (col1->nextCol)
                    col1->nextCol->prevCol = col1;

                col2->nextCol = tmp;
                col2->nextCol->prevCol = col2;

                tmp = col1->prevCol;

                col1->prevCol = col2->prevCol;
                col1->prevCol->nextCol = col1;

                col2->prevCol = tmp;
                if (col2->prevCol)
                    col2->prevCol->nextCol = col2;
            }

            col1->col = j2;
            col1 = col1->nextRow;

            col2->col = j1;
            col2 = col2->nextRow;
        } else if ((col1 && col2 && col1->row < col2->row) || (col1 && !col2)) {
            Cell *prev = col1;
            while (prev->nextCol && prev->nextCol->col < j2)
                prev = prev->nextCol;

            __col_place_next(prev, col1);

            col1->col = j2;
            col1 = col1->nextRow;
        } else {
            Cell *next = col2;
            while (next->prevCol && next->prevCol->col > j1)
                next = next->prevCol;

            __col_place_before(next, col2);

            col2->col = j1;
            col2 = col2->nextRow;
        }
    }

    if (j1 == 0) {
        Index **rows = _csrc_matrix_rows(result);
        Cell *col = csrc_matrix_get_col(result, j2);
        for (size_t i = 0; i < csrc_matrix_shape_n(result); i++) {
            Head *currRow = index_lookup(*rows, i);
            if (!currRow)
                continue;

            while (col && col->row < i)
                col = col->nextRow;

            if (col && col->row == i)
                currRow->head = col;
            else if (currRow->head->col == j2) {
                Cell *h = currRow->head;
                while (h->prevCol)
                    h = h->prevCol;

                currRow->head = h;
            }
        }
    }

    Index *cols = *_csrc_matrix_cols(result);
    Head *h1 = index_lookup(cols, j1);
    Head *h2 = index_lookup(cols, j2);
    Cell *tmp = h1->head;
    h1->head = h2->head;
    h2->head = tmp;

    return result;
}

CsrcMatrix *csrc_matrix_slice(CsrcMatrix *self, size_t i1, size_t j1, size_t i2,
                              size_t j2) {
    size_t self_shape_n = csrc_matrix_shape_n(self);
    size_t self_shape_m = csrc_matrix_shape_m(self);

    if (i1 >= self_shape_n || i2 >= self_shape_n || j1 >= self_shape_m ||
        j2 >= self_shape_m)
        exception_throw_argument("csrc_matrix_slice");

    if (i1 > i2 || (i1 == i2 && j1 > j2)) {
        size_t tmp = i1;
        i1 = i2;
        i2 = tmp;

        tmp = j1;
        j1 = j2;
        j2 = tmp;
    }

    CsrcMatrix *result = csrc_matrix_constructor_z(i2 - i1 + 1, j2 - j1 + 1);

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it);
         // mapa de carnô ((my beloved))
         (curr && curr->row <= i2 && curr->row != i2) ||
         (curr && curr->row <= i2 && curr->col <= j2);
         // he got my back on this one
         curr = csrc_matrix_iterator_forward_row_sparse(it))
        if (curr->col > j2)
            continue;
        else if (curr->row >= i1 && curr->col >= j1)
            csrc_matrix_set(result, curr->row - i1, curr->col - j1, curr->data);

    csrv_matrix_iterator_destructor(it);

    return result;
}

CsrcMatrix *csrc_matrix_transpose(CsrcMatrix *self) {
    size_t self_shape_n = csrc_matrix_shape_n(self);
    size_t self_shape_m = csrc_matrix_shape_m(self);

    CsrcMatrix *result = csrc_matrix_constructor_z(self_shape_m, self_shape_n);

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it))
        csrc_matrix_set(result, curr->col, curr->row, curr->data);

    csrv_matrix_iterator_destructor(it);

    return result;
}

double __kernel_dot(CsrcMatrix *self, CsrcMatrix *kernel, size_t kci,
                    size_t kcj) {
    double result = 0.0;

    size_t self_shape_n = csrc_matrix_shape_n(self);
    size_t self_shape_m = csrc_matrix_shape_m(self);

    size_t kernel_shape_n = csrc_matrix_shape_n(kernel);
    size_t kernel_shape_m = csrc_matrix_shape_m(kernel);

    size_t kernel_center_i = kernel_shape_n / 2;
    size_t kernel_center_j = kernel_shape_m / 2;

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(kernel);
    for (Cell *kcurr = csrc_matrix_iterator_forward_row_sparse(it); kcurr;
         kcurr = csrc_matrix_iterator_forward_row_sparse(it)) {
        if (kcurr->row + kci < kernel_center_i)
            continue;

        size_t s_target_i = kcurr->row + kci - kernel_center_i;
        if (s_target_i >= self_shape_n)
            break;

        if (kcurr->col + kcj < kernel_center_j)
            continue;

        size_t s_target_j = kcurr->col + kcj - kernel_center_j;
        if (s_target_j >= self_shape_m)
            break;

        double scurr_value = csrc_matrix_get(self, s_target_i, s_target_j);

        result += kcurr->data * scurr_value;
    }

    csrv_matrix_iterator_destructor(it);

    return result;
}

CsrcMatrix *csrc_matrix_convolution(CsrcMatrix *self, CsrcMatrix *kernel) {
    size_t self_shape_n = csrc_matrix_shape_n(self);
    size_t self_shape_m = csrc_matrix_shape_m(self);

    size_t kernel_shape_n = csrc_matrix_shape_n(kernel);
    size_t kernel_shape_m = csrc_matrix_shape_m(kernel);

    if (kernel_shape_n % 2 == 0 || kernel_shape_m % 2 == 0)
        exception_throw_argument("csrc_matrix_convolution");

    if (self_shape_n < kernel_shape_n || self_shape_m < kernel_shape_m)
        exception_throw_argument("csrc_matrix_convolution");

    CsrcMatrix *result = csrc_matrix_constructor_z(self_shape_n, self_shape_m);

    size_t kernel_center_i = kernel_shape_n / 2;
    size_t kernel_center_j = kernel_shape_m / 2;

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it)) {
        for (size_t ki = 0; ki < kernel_shape_n; ki++) {
            if (curr->row + ki < kernel_center_i)
                continue;

            size_t k_target_i = curr->row + ki - kernel_center_i;
            if (k_target_i >= self_shape_n)
                break;

            for (size_t kj = 0; kj < kernel_shape_m; kj++) {
                if (curr->col + kj < kernel_center_j)
                    continue;

                size_t k_target_j = curr->col + kj - kernel_center_j;
                if (k_target_j >= self_shape_m)
                    break;

                double k_target_curr_value =
                    csrc_matrix_get(result, k_target_i, k_target_j);
                if (k_target_curr_value != 0)
                    continue;

                csrc_matrix_set(
                    result, k_target_i, k_target_j,
                    __kernel_dot(self, kernel, k_target_i, k_target_j));
            }
        }
    }

    csrv_matrix_iterator_destructor(it);

    return result;
}
