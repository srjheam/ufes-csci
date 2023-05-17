#include <stdlib.h>

#include "csci/cell.h"

#include "csci/csrc_matrix_iterator.h"

struct CsrcMatrixIterator
{
    CsrcMatrix *matrix;
    size_t row;
    size_t col;
    Cell *curr;
};

CsrcMatrixIterator *csrc_matrix_iterator_begin(CsrcMatrix *mat) {
    CsrcMatrixIterator *iterator = (CsrcMatrixIterator *)malloc(sizeof(CsrcMatrixIterator));

    iterator->matrix = mat;
    iterator->row = 0;
    iterator->col = 0;

    Cell *curr = NULL;
    for (size_t i = 0; !curr && i < csrc_matrix_shape_n(mat); i++)    
        curr = csrc_matrix_get_row(mat, i);    

    return iterator;
}

double *csrc_matrix_iterator_forward(CsrcMatrixIterator *self) {
    
}

void csrc_matrix_iterator_destructor(CsrcMatrixIterator *self) {
    free(self);
}
