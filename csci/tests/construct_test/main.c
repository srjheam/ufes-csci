#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_out.h"

int main()
{
    size_t shape_n;
    size_t shape_m;
    scanf("%lu %lu", &shape_n, &shape_m);

    CsrcMatrix *matrix = csrc_matrix_constructor_z(shape_n, shape_m);

    csrc_matrix_print_dense(matrix);

    csrc_matrix_destructor(matrix);

    return EXIT_SUCCESS;
}
