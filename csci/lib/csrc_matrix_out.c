#include <stdio.h>

#include "dsa/exceptions.h"

#include "csci/csrc_matrix_iterator.h"

#include "csci/csrc_matrix_out.h"

void csrc_matrix_print_sparse(CsrcMatrix *self) {
    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it))
        printf("(%lu, %lu) = %.2f\n", curr->row, curr->col, curr->data);

    csrv_matrix_iterator_destructor(it);
}

void csrc_matrix_print_dense(CsrcMatrix *self) {
    printf("[[");

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    for (const double *curr = csrc_matrix_iterator_forward_row_dense(it); curr;
         curr = csrc_matrix_iterator_forward_row_dense(it)) {
        if (csrc_matrix_iterator_get_j(it) == 0 &&
            csrc_matrix_iterator_get_i(it) != 0)
            printf(" [");

        printf(" %.2f", *curr);

        if (csrc_matrix_iterator_get_j(it) == csrc_matrix_shape_m(self) - 1) {
            printf(" ]");

            if (csrc_matrix_iterator_get_i(it) != csrc_matrix_shape_n(self) - 1)
                printf("\n");
        } else
            printf(" ");
    }

    csrv_matrix_iterator_destructor(it);

    printf("]\n");
}

void csrc_matrix_save(CsrcMatrix *self, char *path) {
    FILE *fbin = fopen(path, "wb");

    size_t shape_n = csrc_matrix_shape_n(self);
    size_t shape_m = csrc_matrix_shape_m(self);
    if (fwrite(&shape_n, sizeof shape_n, 1, fbin) != 1) {
        exception_throw_failure(
            "Error saving matrix cell shape_n to binary file - at "
            "csrc_matrix_out.csrv_matrix_save");
    }
    if (fwrite(&shape_m, sizeof shape_n, 1, fbin) != 1) {
        exception_throw_failure(
            "Error saving matrix cell shape_m to binary file - at "
            "csrc_matrix_out.csrv_matrix_save");
    }

    CsrcMatrixIterator *it = csrc_matrix_iterator_begin(self);
    for (Cell *curr = csrc_matrix_iterator_forward_row_sparse(it); curr;
         curr = csrc_matrix_iterator_forward_row_sparse(it)) {
        if (fwrite(&curr->row, sizeof curr->row, 1, fbin) != 1) {
            exception_throw_failure(
                "Error saving matrix cell row to binary file - at "
                "csrc_matrix_out.csrv_matrix_save");
        }
        if (fwrite(&curr->col, sizeof curr->col, 1, fbin) != 1) {
            exception_throw_failure(
                "Error saving matrix cell col to binary file - at "
                "csrc_matrix_out.csrv_matrix_save");
        }
        if (fwrite(&curr->data, sizeof curr->data, 1, fbin) != 1) {
            exception_throw_failure(
                "Error saving matrix cell data to binary file - at "
                "csrc_matrix_out.csrv_matrix_save");
        }
    }

    csrv_matrix_iterator_destructor(it);

    fclose(fbin);
}

CsrcMatrix *csrc_matrix_load(char *path) {
    FILE *fbin = fopen(path, "rb");

    size_t shape_n;
    size_t shape_m;
    if (fread(&shape_n, sizeof shape_n, 1, fbin) != 1) {
        exception_throw_failure(
            "Error loading matrix cell shape_n from binary file - at "
            "csrc_matrix_out.csrv_matrix_load");
    }
    if (fread(&shape_m, sizeof shape_m, 1, fbin) != 1) {
        exception_throw_failure(
            "Error loading matrix cell shape_m from binary file - at "
            "csrc_matrix_out.csrv_matrix_load");
    }

    CsrcMatrix *self = csrc_matrix_constructor_z(shape_n, shape_m);

    size_t row;
    while (fread(&row, sizeof row, 1, fbin) == 1) {
        size_t col;
        if (fread(&col, sizeof col, 1, fbin) != 1) {
            exception_throw_failure(
                "Error loading matrix cell col from binary file - at "
                "csrc_matrix_out.csrv_matrix_load");
        }

        double data;
        if (fread(&data, sizeof data, 1, fbin) != 1) {
            exception_throw_failure(
                "Error loading matrix cell data from binary file - at "
                "csrc_matrix_out.csrv_matrix_load");
        }

        csrc_matrix_set(self, row, col, data);
    }

    fclose(fbin);

    return self;
}

CsrcMatrix *csrc_matrix_read() {
    size_t shape_n;
    size_t shape_m;
    scanf("%lu %lu", &shape_n, &shape_m);

    CsrcMatrix *self = csrc_matrix_constructor_z(shape_n, shape_m);

    size_t row;
    size_t col;
    double data;
    while (scanf("%lu %lu %lf", &row, &col, &data) == 3)
        csrc_matrix_set(self, row, col, data);

    return self;
}
