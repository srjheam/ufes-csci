#include <stdio.h>

#include "rbtree.h"

int intcmp(const int *a, const int *b) { return *a - *b; }

void print_tree(rbtree *root) {
    if (root == NULL)
        return;

    void *it = rbtree_iterator_begin(root);
    int *curr;
    while ((curr = rbtree_iterator_forward(&it)))
        printf("%d ", *(int *)curr);
    
    printf("\n");
}

void print_rtree(rbtree *root) {
    if (root == NULL)
        return;

    void *it = rbtree_iterator_end(root);
    int *curr;
    while ((curr = rbtree_iterator_reverse(&it)))
        printf("%d ", *(int *)curr);
    
    printf("\n");
}

int main() {
    rbtree *t = rbtree_constructor((compar_fn)intcmp, NULL);

    int a = 123;
    rbtree_insert(t, &a);

    int b = 213;
    rbtree_insert(t, &b);

    int c = 3;
    rbtree_insert(t, &c);

    int j = 3;
    rbtree_insert(t, &j);

    int k = 765;
    rbtree_insert(t, &k);

    int d = 765;
    rbtree_insert(t, &d);

    int e = 2;
    rbtree_insert(t, &e);

    int f = 5;
    rbtree_insert(t, &f);

    int g = 0;
    rbtree_insert(t, &g);

    int h = -12;
    rbtree_insert(t, &h);

    int i = 564;
    rbtree_insert(t, &i);

    print_tree(t);
    print_rtree(t);

    rbtree_destructor(t);

    return 0;
}
