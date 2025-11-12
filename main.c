#include <stdio.h>
#include "AVLTree.h"

int main () {
    AVLNode* root = newNode(15);

    printf ("Valor de la raiz: %d\n", root->m_data);
    return 0; 
}
