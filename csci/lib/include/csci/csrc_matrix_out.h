#ifndef _CSCI_CSRC_MATRIX_OUT_H_
#define _CSCI_CSRC_MATRIX_OUT_H_

#include "csci/csrc_matrix.h"

void csrc_matrix_print_sparse(CsrcMatrix *self);

void csrc_matrix_print_dense(CsrcMatrix *self);

void csrc_matrix_save(CsrcMatrix *self, char *path);

CsrcMatrix *csrc_matrix_load(char *path);

CsrcMatrix *csrc_matrix_read();

#endif
