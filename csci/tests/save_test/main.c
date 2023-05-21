#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    CsrcMatrix *a = csrc_matrix_read();

    csrc_matrix_save(a, "out.bin");

    csrc_matrix_destructor(a);

    CsrcMatrix *l = csrc_matrix_load("out.bin");

    csrc_matrix_print_dense(l);

    csrc_matrix_destructor(l);

    return EXIT_SUCCESS;
}
