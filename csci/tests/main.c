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

    printf("###### IDENTITY MATRIX ######\n");

    CsrcMatrix *id = csrc_matrix_indentity(3);

    csrc_matrix_print_sparse(id);

    printf("###### MATRIX MULTIPLICATION ######\n");

    printf("mat:\n");

    csrc_matrix_print_sparse(mat);

    printf("id:\n");

    csrc_matrix_print_sparse(id);

    CsrcMatrix *mulmatid = csrc_matrix_mul(mat, id);

    printf("mulmatid == mat: %s\n",
           csrc_matrix_compar(mulmatid, mat) != 0 ? "true" : "false");

    csrc_matrix_print_sparse(mulmatid);

    printf("###### MATRIX DOT PRODUCT ######\n");

    CsrcMatrix *dotm = csrc_matrix_dot(mat, mulmatid);

    printf("mat:\n");
    csrc_matrix_print_sparse(mat);

    printf("mulmatid:\n");
    csrc_matrix_print_sparse(mulmatid);

    printf("quadratic after dot product:\n");
    csrc_matrix_print_sparse(dotm);

    printf("###### MATRIX TRANSPOSE ######\n");

    CsrcMatrix *tmat = csrc_matrix_transpose(mat);

    printf("mat:\n");

    csrc_matrix_print_dense(mat);

    printf("tmat:\n");

    csrc_matrix_print_dense(tmat);

    CsrcMatrix *ttmat = csrc_matrix_transpose(tmat);

    printf("ttmat:\n");

    csrc_matrix_print_dense(ttmat);

    printf("ttmat == mat: %s\n",
           csrc_matrix_compar(ttmat, mat) != 0 ? "true" : "false");

    printf("###### ROWS SWAP ######\n");

    printf("mat:\n");

    csrc_matrix_print_dense(mat);

    CsrcMatrix *swamat = csrc_matrix_swap_rows(mat, 1, 2);

    printf("swamat:\n");

    csrc_matrix_print_dense(swamat);

    CsrcMatrix *swa2mat = csrc_matrix_swap_rows(swamat, 2, 1);

    printf("swa2mat:\n");

    csrc_matrix_print_dense(swa2mat);

    printf("swa2mat == mat: %s\n",
           csrc_matrix_compar(swa2mat, mat) != 0 ? "true" : "false");

    printf("###### COLUMNS SWAP ######\n");

    printf("mat:\n");

    csrc_matrix_print_dense(mat);

    CsrcMatrix *swbmat = csrc_matrix_swap_cols(mat, 0, 2);

    printf("swbmat:\n");

    csrc_matrix_print_dense(swbmat);

    CsrcMatrix *swb2mat = csrc_matrix_swap_cols(swbmat, 2, 0);

    printf("swb2mat:\n");

    csrc_matrix_print_dense(swb2mat);

    printf("swb2mat == mat: %s\n",
           csrc_matrix_compar(swb2mat, mat) != 0 ? "true" : "false");

    printf("###### MATRIX SLICE ######\n");

    printf("mat:\n");

    csrc_matrix_print_dense(mat);

    CsrcMatrix *slicemat = csrc_matrix_slice(mat, 1, 0, 2, 2);

    printf("slicemat:\n");

    csrc_matrix_print_dense(slicemat);

    CsrcMatrix *sliceslicemat = csrc_matrix_slice(slicemat, 0, 0, 0, 2);

    printf("sliceslicemat:\n");

    csrc_matrix_print_dense(sliceslicemat);

    CsrcMatrix *lineslicemat = csrc_matrix_slice(mat, 1, 0, 1, 2);

    printf("lineslicemat:\n");

    csrc_matrix_print_dense(lineslicemat);

    printf("lineslicemat == sliceslicemat: %s\n",
           csrc_matrix_compar(lineslicemat, sliceslicemat) != 0 ? "true"
                                                                : "false");

    printf("###### MATRIX CONVOLUTION ######\n");

    CsrcMatrix *sconv = csrc_matrix_constructor_z(7, 7);

    csrc_matrix_set(sconv, 0, 0, 0);
    csrc_matrix_set(sconv, 0, 1, 1);
    csrc_matrix_set(sconv, 0, 2, 1);
    csrc_matrix_set(sconv, 0, 3, 1);
    csrc_matrix_set(sconv, 0, 4, 0);
    csrc_matrix_set(sconv, 0, 5, 0);
    csrc_matrix_set(sconv, 0, 6, 0);

    csrc_matrix_set(sconv, 1, 0, 0);
    csrc_matrix_set(sconv, 1, 1, 0);
    csrc_matrix_set(sconv, 1, 2, 1);
    csrc_matrix_set(sconv, 1, 3, 1);
    csrc_matrix_set(sconv, 1, 4, 1);
    csrc_matrix_set(sconv, 1, 5, 0);
    csrc_matrix_set(sconv, 1, 6, 0);

    csrc_matrix_set(sconv, 2, 0, 0);
    csrc_matrix_set(sconv, 2, 1, 0);
    csrc_matrix_set(sconv, 2, 2, 0);
    csrc_matrix_set(sconv, 2, 3, 1);
    csrc_matrix_set(sconv, 2, 4, 1);
    csrc_matrix_set(sconv, 2, 5, 1);
    csrc_matrix_set(sconv, 2, 6, 0);

    csrc_matrix_set(sconv, 3, 0, 0);
    csrc_matrix_set(sconv, 3, 1, 0);
    csrc_matrix_set(sconv, 3, 2, 0);
    csrc_matrix_set(sconv, 3, 3, 1);
    csrc_matrix_set(sconv, 3, 4, 1);
    csrc_matrix_set(sconv, 3, 5, 0);
    csrc_matrix_set(sconv, 3, 6, 0);

    csrc_matrix_set(sconv, 4, 0, 0);
    csrc_matrix_set(sconv, 4, 1, 0);
    csrc_matrix_set(sconv, 4, 2, 1);
    csrc_matrix_set(sconv, 4, 3, 1);
    csrc_matrix_set(sconv, 4, 4, 0);
    csrc_matrix_set(sconv, 4, 5, 0);
    csrc_matrix_set(sconv, 4, 6, 0);

    csrc_matrix_set(sconv, 5, 0, 0);
    csrc_matrix_set(sconv, 5, 1, 1);
    csrc_matrix_set(sconv, 5, 2, 1);
    csrc_matrix_set(sconv, 5, 3, 0);
    csrc_matrix_set(sconv, 5, 4, 0);
    csrc_matrix_set(sconv, 5, 5, 0);
    csrc_matrix_set(sconv, 5, 6, 0);

    csrc_matrix_set(sconv, 6, 0, 1);
    csrc_matrix_set(sconv, 6, 1, 1);
    csrc_matrix_set(sconv, 6, 2, 0);
    csrc_matrix_set(sconv, 6, 3, 0);
    csrc_matrix_set(sconv, 6, 4, 0);
    csrc_matrix_set(sconv, 6, 5, 0);
    csrc_matrix_set(sconv, 6, 6, 0);

    printf("sconv:\n");

    csrc_matrix_print_dense(sconv);

    CsrcMatrix *kernel = csrc_matrix_constructor_z(3, 3);

    csrc_matrix_set(kernel, 0, 0, 1);
    csrc_matrix_set(kernel, 0, 1, 0);
    csrc_matrix_set(kernel, 0, 2, 1);

    csrc_matrix_set(kernel, 1, 0, 0);
    csrc_matrix_set(kernel, 1, 1, 1);
    csrc_matrix_set(kernel, 1, 2, 0);

    csrc_matrix_set(kernel, 2, 0, 1);
    csrc_matrix_set(kernel, 2, 1, 0);
    csrc_matrix_set(kernel, 2, 2, 1);

    printf("kernel:\n");

    csrc_matrix_print_dense(kernel);

    CsrcMatrix *convsconv = csrc_matrix_convolution(sconv, kernel);

    printf("convsconv:\n");

    csrc_matrix_print_dense(convsconv);

    CsrcMatrix *sliceconv = csrc_matrix_slice(convsconv, 1, 1, 5, 5);

    printf("sliceconv:\n");

    csrc_matrix_print_dense(sliceconv);

    CsrcMatrix *slicetarget = csrc_matrix_constructor_z(5, 5);

    csrc_matrix_set(slicetarget, 0, 0, 1);
    csrc_matrix_set(slicetarget, 0, 1, 4);
    csrc_matrix_set(slicetarget, 0, 2, 3);
    csrc_matrix_set(slicetarget, 0, 3, 4);
    csrc_matrix_set(slicetarget, 0, 4, 1);

    csrc_matrix_set(slicetarget, 1, 0, 1);
    csrc_matrix_set(slicetarget, 1, 1, 2);
    csrc_matrix_set(slicetarget, 1, 2, 4);
    csrc_matrix_set(slicetarget, 1, 3, 3);
    csrc_matrix_set(slicetarget, 1, 4, 3);

    csrc_matrix_set(slicetarget, 2, 0, 1);
    csrc_matrix_set(slicetarget, 2, 1, 2);
    csrc_matrix_set(slicetarget, 2, 2, 3);
    csrc_matrix_set(slicetarget, 2, 3, 4);
    csrc_matrix_set(slicetarget, 2, 4, 1);

    csrc_matrix_set(slicetarget, 3, 0, 1);
    csrc_matrix_set(slicetarget, 3, 1, 3);
    csrc_matrix_set(slicetarget, 3, 2, 3);
    csrc_matrix_set(slicetarget, 3, 3, 1);
    csrc_matrix_set(slicetarget, 3, 4, 1);

    csrc_matrix_set(slicetarget, 4, 0, 3);
    csrc_matrix_set(slicetarget, 4, 1, 3);
    csrc_matrix_set(slicetarget, 4, 2, 1);
    csrc_matrix_set(slicetarget, 4, 3, 1);
    csrc_matrix_set(slicetarget, 4, 4, 0);

    printf("slicetarget:\n");

    csrc_matrix_print_dense(slicetarget);

    printf("sliceconv == slicetarget: %s\n",
           csrc_matrix_compar(sliceconv, slicetarget) ? "true" : "false");

    csrc_matrix_destructor(sliceconv);
    csrc_matrix_destructor(convsconv);
    csrc_matrix_destructor(kernel);
    csrc_matrix_destructor(sconv);

    csrc_matrix_destructor(lineslicemat);
    csrc_matrix_destructor(sliceslicemat);
    csrc_matrix_destructor(slicemat);

    csrc_matrix_destructor(swamat);
    csrc_matrix_destructor(swa2mat);
    csrc_matrix_destructor(swbmat);

    csrc_matrix_destructor(ttmat);
    csrc_matrix_destructor(tmat);

    csrc_matrix_destructor(dotm);
    csrc_matrix_destructor(mulmatid);
    csrc_matrix_destructor(id);
    csrc_matrix_destructor(mat);
    csrc_matrix_destructor(lmat);

    return 0;
}
