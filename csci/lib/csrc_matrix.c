#include "csci/index.h"

#include "csci/csrc_matrix.h"

struct CsrcMatrix
{
    int shape_n;
    int shape_m;

    enum dtype dtype;

    Index *rows;
    Index *cols;
};

CsrcMatrix *csrc_matrix_constructor_z(int n, int m, enum dtype dtype) {
    CsrcMatrix *self = malloc(sizeof *self);

    self->shape_n = n;
    self->shape_m = m;

    self->dtype = dtype;

    compar_fn compar;
    switch (self->dtype)
    {
    case INT32:
        compar = (compar_fn)common_int32_compar;
        break;
    
    case FLOAT32:
        compar = (compar_fn)common_float32_compar;
        break;

    case DOUBLE64:
        compar = (compar_fn)common_double64_compar;
        break;
    }

    self->rows = index_constructor(compar);;
    self->cols = index_constructor(compar);;

    return self;
}

void *csrc_matrix_get(CsrcMatrix *self, int i, int j) {
    list *row = index_lookup(self->rows, i);
    if (!row) {
        return NULL;
    }

    
    
}

void csrc_matrix_set(CsrcMatrix *self, int i, int j, void *value);

void *csrc_matrix_iterator_begin(CsrcMatrix *self);

void *csrc_matrix_iterator_forward(CsrcMatrix *self);

void *csrc_matrix_iterator_end(CsrcMatrix *self);

void csrc_matrix_print(CsrcMatrix *self);

void csrc_matrix_clear(CsrcMatrix *self);

void csrc_matrix_destructor(CsrcMatrix *self);
