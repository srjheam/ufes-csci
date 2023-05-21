#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    CsrcMatrix *a = csrc_matrix_read();

    size_t row1, row2;
    scanf("%lu %lu", &row1, &row2);

    CsrcMatrix *res = csrc_matrix_swap_rows(a, row1, row2);

    csrc_matrix_print_dense(res);

    csrc_matrix_destructor(res);
    csrc_matrix_destructor(a);

    return EXIT_SUCCESS;
}
