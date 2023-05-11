#include "rbtree.h"

int intcmp(const int *a, const int *b) {
    return *a - *b;
}

int main()
{
    rbtree *t = rbtree_constructor(sizeof(int), (compar_fn)intcmp);

    int a = 123;
    rbtree_insert(t, &a);

    a = 213;
    rbtree_insert(t, &a);

    a = 3;
    rbtree_insert(t, &a);

    a = 765;
    rbtree_insert(t, &a);

    a = 2;
    rbtree_insert(t, &a);

    a = 5;
    rbtree_insert(t, &a);

    a = 0;
    rbtree_insert(t, &a);

    a = -12;
    rbtree_insert(t, &a);

    a = 564;
    rbtree_insert(t, &a);


    rbtree_destructor(t);


    return 0;
}
