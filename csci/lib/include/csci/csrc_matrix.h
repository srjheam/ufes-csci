#ifndef _CSCI_CSRC_MATRIX_H_
#define _CSCI_CSRC_MATRIX_H_

#include "csci/common.h"

typedef struct CsrcMatrix CsrcMatrix;

CsrcMatrix *csrc_matrix_constructor_z(int n, int m);

double csrc_matrix_get(CsrcMatrix *self, int i, int j);

Cell *csrc_matrix_get_row(CsrcMatrix *self, int i);

Cell *csrc_matrix_get_col(CsrcMatrix *self, int j);

size_t csrc_matrix_shape_n(CsrcMatrix *self);

size_t csrc_matrix_shape_m(CsrcMatrix *self);

void csrc_matrix_set(CsrcMatrix *self, int i, int j, double value);

void csrc_matrix_print_sparse(CsrcMatrix *self);

void csrc_matrix_clear(CsrcMatrix *self);

void csrc_matrix_destructor(CsrcMatrix *self);

#endif