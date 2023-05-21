#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    CsrcMatrix *a = csrc_matrix_read();

    size_t i1, j1, i2, j2;
    scanf("%lu %lu %lu %lu", &i1, &j1, &i2, &j2);

    CsrcMatrix *slice = csrc_matrix_slice(a, i1, j1, i2, j2);

    csrc_matrix_print_dense(slice);

    csrc_matrix_destructor(slice);
    csrc_matrix_destructor(a);

    return EXIT_SUCCESS;
}
