#include <assert.h>
#include <stdio.h>

#include "csci/csrc_matrix.h"
#include "csci/csrc_matrix_iterator.h"
#include "csci/csrc_matrix_oper.h"
#include "csci/csrc_matrix_out.h"

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

    csrc_matrix_set(mat, 0, 1, 0);
    csrc_matrix_set(mat, 1, 0, 0);
    csrc_matrix_set(mat, 2, 2, 0);

    csrc_matrix_print_sparse(mat);

    csrc_matrix_print_dense(mat);

    assert(csrc_matrix_get(mat, 0, 0) == 1);
    assert(csrc_matrix_get(mat, 0, 1) == 0);
    assert(csrc_matrix_get(mat, 0, 2) == 3);
    assert(csrc_matrix_get(mat, 1, 0) == 0);
    assert(csrc_matrix_get(mat, 1, 1) == 5);
    assert(csrc_matrix_get(mat, 1, 2) == 6);
    assert(csrc_matrix_get(mat, 2, 0) == 7);
    assert(csrc_matrix_get(mat, 2, 1) == 8);
    assert(csrc_matrix_get(mat, 2, 2) == 0);

    csrc_matrix_save(mat, "./test_matrix.bin");

    CsrcMatrix *lmat = csrc_matrix_load("./test_matrix.bin");

    csrc_matrix_print_sparse(mat);
    csrc_matrix_print_sparse(lmat);

    printf("mat == lmat: %s\n",
           csrc_matrix_compar(mat, lmat) != 0 ? "true" : "false");

    CsrcMatrix *sdouble = csrc_matrix_add(mat, lmat);
    CsrcMatrix *mdouble = csrc_matrix_mul_scalar(lmat, 2);

    printf("sdouble == mdouble: %s\n",
           csrc_matrix_compar(sdouble, mdouble) != 0 ? "true" : "false");

    csrc_matrix_print_sparse(sdouble);
    csrc_matrix_print_sparse(mdouble);

    CsrcMatrix *id = csrc_matrix_indentity(3);

    csrc_matrix_print_sparse(id);

    CsrcMatrix *mulmatid = csrc_matrix_mul(mat, id);

    printf("mulmatid == mat: %s\n",
           csrc_matrix_compar(mulmatid, mat) != 0 ? "true" : "false");

    csrc_matrix_destructor(mulmatid);
    csrc_matrix_destructor(id);
    csrc_matrix_destructor(mat);
    csrc_matrix_destructor(lmat);

    return 0;
}
