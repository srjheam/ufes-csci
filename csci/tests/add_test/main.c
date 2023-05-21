#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    CsrcMatrix *a = csrc_matrix_read();
    CsrcMatrix *b = csrc_matrix_read();

    CsrcMatrix *res = csrc_matrix_add(a, b);

    csrc_matrix_print_dense(res);

    csrc_matrix_destructor(res);
    csrc_matrix_destructor(b);
    csrc_matrix_destructor(a);

    return EXIT_SUCCESS;
}
