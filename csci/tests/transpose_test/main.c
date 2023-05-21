#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    CsrcMatrix *s = csrc_matrix_read();

    // St
    CsrcMatrix *t = csrc_matrix_transpose(s);

    csrc_matrix_print_dense(t);

    // (St)t == S
    CsrcMatrix *tt = csrc_matrix_transpose(t);

    csrc_matrix_print_dense(tt);

    size_t escalar;
    scanf("%lu", &escalar);

    // (escalar * S)t == escalar * St

    CsrcMatrix *ks = csrc_matrix_mul_scalar(s, escalar);

    CsrcMatrix *kst = csrc_matrix_transpose(ks);

    csrc_matrix_print_dense(kst);

    CsrcMatrix *k_st = csrc_matrix_mul_scalar(t, escalar);

    csrc_matrix_print_dense(k_st);

    // (S + B)t == St + Bt

    // (SB)t == BtSt

    csrc_matrix_destructor(k_st);
    csrc_matrix_destructor(kst);
    csrc_matrix_destructor(ks);
    csrc_matrix_destructor(tt);
    csrc_matrix_destructor(t);
    csrc_matrix_destructor(s);

    return EXIT_SUCCESS;
}
