#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    CsrcMatrix *a = csrc_matrix_read();
    CsrcMatrix *b = csrc_matrix_read();

    CsrcMatrix *mul = csrc_matrix_mul(a, b);

    csrc_matrix_print_dense(mul);

    csrc_matrix_destructor(mul);
    csrc_matrix_destructor(b);
    csrc_matrix_destructor(a);

    return EXIT_SUCCESS;
}
