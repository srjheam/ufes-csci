#include "dsa/list.h"

#include "csci/head.h"

size_t head_index(const Head *head) { return head->i; }

Cell *head_first(const Head *head) { return head->head; }

int head_compar(const Head *a, const Head *b) { return a->i - b->i; }
