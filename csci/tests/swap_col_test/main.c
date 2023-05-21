#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    CsrcMatrix *a = csrc_matrix_read();

    size_t col1, col2;
    scanf("%lu %lu", &col1, &col2);

    CsrcMatrix *res = csrc_matrix_swap_cols(a, col1, col2);

    csrc_matrix_print_dense(res);

    csrc_matrix_destructor(res);
    csrc_matrix_destructor(a);

    return EXIT_SUCCESS;
}
