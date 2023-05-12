#include <stdio.h>

#include "rbtree.h"

int intcmp(const int *a, const int *b) {
    return *a - *b;
}

void print_tree(rbtree *root) {
    if (root == NULL)
        return;

    void *it = rbtree_iterator_begin(root);
    while (rbtree_iterator_has_next(&it))
        printf("%d ", *(int *)rbtree_iterator_next(&it));    
}

int main()
{
    rbtree *t = rbtree_constructor((compar_fn)intcmp, NULL);

    int a = 123;
    rbtree_insert(t, &a);

    int b = 213;
    rbtree_insert(t, &b);

    int c = 3;
    rbtree_insert(t, &c);

    print_tree(t);

    rbtree_destructor(t);

    return 0;
}
