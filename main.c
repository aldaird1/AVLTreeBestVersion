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
    insert (&root, 5);
    insert (&root, 4);
    insert (&root, 3);
    insert (&root, 2);
    insert (&root, 10);

    printf ("Valor de la raiz: %d\n", root->m_data);
    printTree (root);

    for (int i= 0; i < 5; i++) {
        insert (&root, i -3);
	printf ("Aca esta el tree:\n");
	    printTree (root);	
    }
    printf ("Rotación a la izquierda del arbol del  izquierdo\n");
    root->m_left = leftRotate (root->m_left);
    printTree (root);
    printf ("Rotación a la derecha del arbol del  izquierdo\n");
    root->m_right = rightRotate (root->m_right);
    printTree (root);
    return 0; 
}
