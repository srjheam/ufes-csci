#ifndef _CSCI_CELL_H_
#define _CSCI_CELL_H_

#include "dsa/common.h"

typedef struct Cell Cell;

Cell *cell_constructor(int row, int col, void *data);

void cell_destructor(Cell *cell, destruct_fn destructor);

#endif
