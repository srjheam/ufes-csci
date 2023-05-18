#include "csci/cell.h"

Cell *cell_constructor(size_t row, size_t col, double data) {
    Cell *self = malloc(sizeof *self);

    self->row = row;
    self->col = col;

    self->nextCol = NULL;
    self->nextRow = NULL;
    self->prevCol = NULL;
    self->prevRow = NULL;

    self->data = data;

    return self;
}

void cell_remove(Cell *cell) {
    if (cell->prevRow)
        cell->prevRow->nextRow = cell->nextRow;
    if (cell->nextRow)
        cell->nextRow->prevRow = cell->prevRow;
    if (cell->prevCol)
        cell->prevCol->nextCol = cell->nextCol;
    if (cell->nextCol)
        cell->nextCol->prevCol = cell->prevCol;

    cell->data = 0;
}

void cell_destructor(Cell *cell) {
    free(cell);
}
