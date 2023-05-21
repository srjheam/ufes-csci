#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    size_t escalar;
    scanf("%lu", &escalar);

    CsrcMatrix *a = csrc_matrix_read();

    CsrcMatrix *mul = csrc_matrix_mul_scalar(a, escalar);

    csrc_matrix_print_dense(mul);

    csrc_matrix_destructor(mul);
    csrc_matrix_destructor(a);

    return EXIT_SUCCESS;
}
