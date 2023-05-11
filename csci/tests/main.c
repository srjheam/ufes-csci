#include <stdio.h>

#include "rbtree.h"

int intcmp(const int *a, const int *b) {
    return *a - *b;
}

void print_tree(rbnode *root, int level) {
    if (root == NULL)
        return;

    print_tree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("%d\n", *(int *)root->key);

    print_tree(root->left, level + 1);
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

    print_tree(t->root, 0);

    rbtree_destructor(t);

    return 0;
}
