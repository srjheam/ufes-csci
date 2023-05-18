#include <stdio.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_iterator.h"

int main() {
    CsrcMatrix *mat = csrc_matrix_constructor_z(3, 3);

    csrc_matrix_set(mat, 0, 0, 1);

    csrc_matrix_print_sparse(mat);

    csrc_matrix_print_dense(mat);
    
    csrc_matrix_set(mat, 0, 1, 2);
    csrc_matrix_set(mat, 0, 2, 3);

    csrc_matrix_print_sparse(mat);

    csrc_matrix_print_dense(mat);

    csrc_matrix_set(mat, 1, 0, 4);
    csrc_matrix_set(mat, 1, 1, 5);
    csrc_matrix_set(mat, 1, 2, 6);
    csrc_matrix_set(mat, 2, 0, 7);
    csrc_matrix_set(mat, 2, 1, 8);
    csrc_matrix_set(mat, 2, 2, 9);

    csrc_matrix_print_sparse(mat);

    csrc_matrix_print_dense(mat);

    csrc_matrix_destructor(mat);   

    return 0;
}
