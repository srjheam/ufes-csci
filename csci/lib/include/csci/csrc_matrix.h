#ifndef _CSCI_CSRC_MATRIX_H_
#define _CSCI_CSRC_MATRIX_H_

#include "csci/cell.h"

typedef struct CsrcMatrix CsrcMatrix;

CsrcMatrix *csrc_matrix_constructor_z(size_t n, size_t m);

void csrc_matrix_set(CsrcMatrix *self, size_t i, size_t j, double value);

double csrc_matrix_get(CsrcMatrix *self, size_t i, size_t j);

Cell *csrc_matrix_get_row(CsrcMatrix *self, size_t i);

Cell *csrc_matrix_get_col(CsrcMatrix *self, size_t j);

size_t csrc_matrix_shape_n(CsrcMatrix *self);

size_t csrc_matrix_shape_m(CsrcMatrix *self);

int csrc_matrix_compar(CsrcMatrix *self, CsrcMatrix *b);

CsrcMatrix *csrc_matrix_copy(CsrcMatrix *self);

void csrc_matrix_clear(CsrcMatrix *self);

void csrc_matrix_destructor(CsrcMatrix *self);

#endif