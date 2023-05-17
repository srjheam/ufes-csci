#ifndef _CSCI_CSRC_MATRIX_H_
#define _CSCI_CSRC_MATRIX_H_

#include "csci/common.h"

typedef struct CsrcMatrix CsrcMatrix;

CsrcMatrix *csrc_matrix_constructor_z(int n, int m);

double csrc_matrix_get(CsrcMatrix *self, int i, int j);

void csrc_matrix_set(CsrcMatrix *self, int i, int j, double value);

void *csrc_matrix_iterator_begin(CsrcMatrix *self);

void *csrc_matrix_iterator_forward(CsrcMatrix *self);

void *csrc_matrix_iterator_end(CsrcMatrix *self);

void csrc_matrix_print(CsrcMatrix *self);

void csrc_matrix_clear(CsrcMatrix *self);

void csrc_matrix_destructor(CsrcMatrix *self);

#endif