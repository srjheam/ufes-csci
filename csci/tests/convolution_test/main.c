#include <stdio.h>
#include <stdlib.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

int main() {
    CsrcMatrix *s = csrc_matrix_read();
    CsrcMatrix *kernel = csrc_matrix_read();

    csrc_matrix_print_dense(s);

    CsrcMatrix *conv = csrc_matrix_convolution(s, kernel);

    csrc_matrix_print_dense(conv);

    csrc_matrix_destructor(conv);
    csrc_matrix_destructor(kernel);
    csrc_matrix_destructor(s); */

    return EXIT_SUCCESS;
}
