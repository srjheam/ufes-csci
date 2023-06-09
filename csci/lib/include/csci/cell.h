#ifndef _CSCI_CELL_H_
#define _CSCI_CELL_H_

#include "dsa/common.h"

typedef struct Cell {
    struct Cell *prevRow;
    struct Cell *nextRow;
    struct Cell *prevCol;
    struct Cell *nextCol;

    size_t row;
    size_t col;

    double data;
} Cell;

Cell *cell_constructor(size_t row, size_t col, double data);

void cell_remove(Cell *cell);

void cell_destructor(Cell *cell);

#endif
