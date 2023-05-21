#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    CsrcMatrix *a = csrc_matrix_read();
    CsrcMatrix *b = csrc_matrix_read();

    CsrcMatrix *dot = csrc_matrix_dot(a, b);

    csrc_matrix_print_dense(dot);

    csrc_matrix_destructor(dot);
    csrc_matrix_destructor(b);
    csrc_matrix_destructor(a);

    return EXIT_SUCCESS;
}
