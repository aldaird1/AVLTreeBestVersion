#include "AVLTree.h"
#include "functions.h"

void request (AVLNode** root) {
    while ( si ("¿Deseas continuar?\0")) {

        if (si ("¿Deseas insertar un nuevo nodo?\0")) {
            int a; 
            printf ("Ingresa el valor: \n");
            scanf ("%d", &a);
            insert (root, a);
        }


        if (si ("¿Deseas ver el arbol?\0"))
            printTree (*root);
    }
}

int si (char message []) {
    printf ("%s (y o ENTER = si / cualquier otro = no)\n", message);
    char a = getchar ();

    if (a == 'y' || a == '\n') return 1;
    else return 0;
}
