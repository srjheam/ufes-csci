#ifndef _CSCI_CSRC_MATRIX_H_
#define _CSCI_CSRC_MATRIX_H_

#include "csci/cell.h"
#include "csci/index.h"

typedef struct CsrcMatrix CsrcMatrix;

Index **_csrc_matrix_rows(CsrcMatrix *self);

Index **_csrc_matrix_cols(CsrcMatrix *self);

Cell *_csrc_matrix_get_r(CsrcMatrix *self, size_t i, size_t j);

CsrcMatrix *csrc_matrix_constructor_z(size_t n, size_t m);

CsrcMatrix *csrc_matrix_indentity(size_t n);

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