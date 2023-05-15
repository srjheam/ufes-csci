#include "csci/cell.h"

struct Cell {
    int row;
    int col;

    void *data;
};

Cell *cell_constructor(int row, int col, void *data) {
    Cell *self = malloc(sizeof *self);

    self->row = row;
    self->col = col;

    self->data = data;

    return self;
}

void cell_destructor(Cell *cell, destruct_fn destructor) {
    if (destructor)
        destructor(cell->data);

    free(cell);
}
