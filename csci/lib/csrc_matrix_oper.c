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
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it)) {
        double self_val = csrc_matrix_get(self, curr->row, curr->col);
        if (self_val == 0)
            continue;

        double sum_val = curr->data * self_val;

        double curr_val = csrc_matrix_get(result, curr->row, curr->col);

        csrc_matrix_set(result, curr->row, curr->col, curr_val + sum_val);
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

CsrcMatrix *csrc_matrix_swap_rows(CsrcMatrix *self, size_t i1, size_t i2) {
    size_t self_shape_n = csrc_matrix_shape_n(self);
    size_t self_shape_m = csrc_matrix_shape_m(self);

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

    // todo

    return result;
}

CsrcMatrix *csrc_matrix_swap_cols(CsrcMatrix *self, size_t j1, size_t j2) {
    size_t self_shape_n = csrc_matrix_shape_n(self);
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

    // todo

    return result;
}

CsrcMatrix *csrc_matrix_slice(CsrcMatrix *self, size_t i1, size_t j1, size_t i2,
                              size_t j2) {
    size_t self_shape_n = csrc_matrix_shape_n(self);
    size_t self_shape_m = csrc_matrix_shape_m(self);

    if (i1 >= self_shape_n || i2 >= self_shape_n || j1 >= self_shape_m ||
        j2 >= self_shape_m)
        exception_throw_argument("csrc_matrix_slice");

    if (i1 > i2) {
        size_t tmp = i1;
        i1 = i2;
        i2 = tmp;
    }

    if (j1 > j2) {
        size_t tmp = j1;
        j1 = j2;
        j2 = tmp;
    }

    CsrcMatrix *result = csrc_matrix_constructor_z(i2 - i1, j2 - j1);

    // todo

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

    // todo

    return result;
}
