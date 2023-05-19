#ifndef _CSRC_MATRIX_OPER_H_
#define _CSRC_MATRIX_OPER_H_

#include "csci/csrc_matrix.h"

CsrcMatrix *csrc_matrix_add(CsrcMatrix *self, CsrcMatrix *b);

CsrcMatrix *csrc_matrix_mul_scalar(CsrcMatrix *self, double scalar);

CsrcMatrix *csrc_matrix_mul(CsrcMatrix *self, CsrcMatrix *b);

CsrcMatrix *csrc_matrix_dot(CsrcMatrix *self, CsrcMatrix *b);

CsrcMatrix *csrc_matrix_swap_rows(CsrcMatrix *self, size_t i1, size_t i2);

CsrcMatrix *csrc_matrix_swap_cols(CsrcMatrix *self, size_t j1, size_t j2);

CsrcMatrix *csrc_matrix_slice(CsrcMatrix *self, size_t i1, size_t j1, size_t i2, size_t j2);

CsrcMatrix *csrc_matrix_transpose(CsrcMatrix *self);

CsrcMatrix *csrc_matrix_convolution(CsrcMatrix *self, CsrcMatrix *kernel);

#endif
