#include <stdio.h>
#include "AVLTree.h"

int main () {
    AVLNode* root = NULL;

    insert (&root, 15);

    insert (&root, 12);
    insert (&root, 18);
    insert (&root, 9);
    insert (&root, 13);
    insert (&root, 16);
    insert (&root, 25);

    printf ("Valor de la raiz: %d\n", root->m_data);

    return 0; 
}
