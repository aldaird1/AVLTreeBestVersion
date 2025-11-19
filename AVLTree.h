#ifndef AVLTREE_H
#define AVLTREE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) ((a>b)?a:b)

typedef struct AVLNode {
    int m_height;
    int m_data; 
    struct AVLNode* m_left;
    struct AVLNode* m_right;
    struct AVLNode* m_parent;
}AVLNode;


//======================== DECLARACIONES DE LAS FUNCIONES =================================//
AVLNode* newNode (int); 
int bf (AVLNode* );
int nodeHeight (AVLNode*);
AVLNode* leftRotate (AVLNode*);
AVLNode* rightRotate (AVLNode*);
AVLNode* rebalancing (AVLNode*);

AVLNode* insertIt (AVLNode*, int);//Las alturas de los subarboles a los que no se accede no se modifican
void printTreeRecursive (AVLNode*, int);

void insert (AVLNode**, int);
void printTree (AVLNode*);
//======================== DEFINICONES DE LAS FUNCIONES ===================================//
int bf (AVLNode* node) {
    return nodeHeight (node->m_right) - nodeHeight (node->m_left);	
}

AVLNode* rightRotate (AVLNode* node) {
    assert (node);
    assert (node->m_left); 

    AVLNode* root = node->m_left;
    AVLNode* back = root->m_right;

    root->m_parent = node->m_parent;
    if (root->m_parent){
        if (node == node->m_parent->m_left) node->m_parent->m_left = root;
        else node->m_parent->m_right = root;
    }
    root->m_right = node;
    node->m_parent = root;

    node->m_left = back;
    if (back) back->m_parent = node;

    root->m_right->m_height = 1 + MAX (nodeHeight (root->m_right->m_right), nodeHeight (root->m_right->m_left));
    root->m_height = 1 + MAX (nodeHeight (root->m_right), nodeHeight (root->m_left));

    return root;
}

AVLNode* leftRotate (AVLNode* node) {
    assert (node);
    assert (node->m_right); 

    AVLNode* root = node->m_right;
    AVLNode* back = root->m_left;

    root->m_parent = node->m_parent;
    if (root->m_parent) {
        if (node == node->m_parent->m_left) node->m_parent->m_left = root;
        else node->m_parent->m_right = root;
    }

    root->m_left = node;
    node->m_parent =root;

    node->m_right = back;
    if (back) back->m_parent = node;

    root->m_left->m_height = 1 + MAX (nodeHeight (root->m_left->m_right), nodeHeight (root->m_left->m_left));
    root->m_height = 1 + MAX (nodeHeight (root->m_right), nodeHeight (root->m_left));

    return root;
}

void printTree (AVLNode* node) {printTreeRecursive (node, 1);}

int nodeHeight (AVLNode* node) {
    if (!node) return -1;
    else return node->m_height;
}

void printTreeRecursive (AVLNode* node, int sub) {
    if (!node) return;
    printTreeRecursive (node->m_right, sub + 1);

    for (int i = 1; i < sub; i++) {
        printf ("      ");
    }
    printf ("---- %d(%d)\n", node->m_data, node->m_height);

    printTreeRecursive (node->m_left, sub + 1);
    return;
}


AVLNode* newNode (int _data) {
    AVLNode* nuevoNodo = malloc (sizeof (AVLNode));
    nuevoNodo->m_height = 0;
    nuevoNodo->m_parent = NULL;
    nuevoNodo->m_left = NULL;
    nuevoNodo->m_right = NULL;
    nuevoNodo->m_data = _data;

    return nuevoNodo;
}

AVLNode* insertIt (AVLNode* node, int _data) {
    AVLNode* back = NULL;

    while (node) {//Recorre hasta el final del arbol
        back = node;
        if (_data > node->m_data) node = node->m_right;
        else if (_data < node->m_data) node = node->m_left;
        else return NULL;
    }

    if (!back) return newNode (_data); //En el caso de que el arbol este vacio retorna le nuevo nodo

    if (_data > back->m_data) { //El caso normal en el que se inserta el nodo en la posición que se desea y se retorna un puntero a ese nodo
        back->m_right = newNode (_data);
        back->m_right->m_parent = back;
        return back->m_right;
    } else if (_data < back->m_data) {
        back->m_left = newNode (_data);
        back->m_left->m_parent = back;
        return back->m_left;
    } else return NULL;
}
//



//
void insert (AVLNode** root, int _data) {
    if (!(*root)) {
        *root = insertIt (*root, _data);
        return;
    }

    AVLNode* last = insertIt (*root, _data);
    *root = rebalancing (last);
}


   AVLNode* rebalancing (AVLNode* node) {
   assert (node);
   AVLNode* newRoot = NULL;

   while (node) {
   if (bf (node) == -2) {
   if ( bf (node->m_left) == 1)
   node->m_left = leftRotate (node->m_left);
   newRoot = rightRotate (node);
   node = node->m_parent->m_parent;

   } else if (bf (node) == 2) {
   if (bf (node->m_right) == -1 )
   node->m_right = rightRotate (node->m_right);
   newRoot = leftRotate (node);
   node = node->m_parent->m_parent;

   } else {
   node->m_height = 1 + MAX (nodeHeight (node->m_left), nodeHeight (node->m_right));
   newRoot = node;
   node = node->m_parent;
   }
   }
   return newRoot;
   }

/*
AVLNode* rebalancing(AVLNode* node) {
    assert(node);
    AVLNode* newRoot = node; // Mantener rastro de la última raíz procesada
                             // Mientras exista un nodo (subimos hasta la raíz global)
    while (node) {

        // 1. PRIMERO: Actualizar la altura del nodo actual
        // Es vital hacer esto ANTES de chequear el balance o rotar
        node->m_height = 1 + MAX(nodeHeight(node->m_left), nodeHeight(node->m_right));

        // 2. Calcular balance
        int balance = bf(node);

        // 3. Caso: Pesado a la Izquierda
        if (balance == -2) {
            // Chequear si es caso Left-Right (Zig-Zag)
            if (bf(node->m_left) == 1) { 
                node->m_left = leftRotate(node->m_left);
            }
            // Aplicar rotación derecha (corrige Left-Left y el final de Left-Right)
            // IMPORTANTE: Guardar el resultado de la rotación
            AVLNode* subtreeRoot = rightRotate(node);

            // Si este nodo era la raíz global, actualizamos newRoot
            if (subtreeRoot->m_parent == NULL) {
                newRoot = subtreeRoot;
            }

            // OJO: Después de rotar, 'node' ha bajado. 
            // Debemos seguir el camino hacia arriba desde la NUEVA raíz de este subárbol.
            node = subtreeRoot; 
        } 

        // 4. Caso: Pesado a la Derecha
        else if (balance == 2) {
            // Chequear si es caso Right-Left (Zig-Zag)
            if (bf(node->m_right) == -1) {
                node->m_right = rightRotate(node->m_right);
            }
            // Aplicar rotación izquierda
            AVLNode* subtreeRoot = leftRotate(node);

            if (subtreeRoot->m_parent == NULL) {
                newRoot = subtreeRoot;
            }

            node = subtreeRoot;
        }

        // 5. Avanzar hacia arriba (al padre)
        // Si rotamos, 'node' ahora es la cabeza del subárbol, así que vamos a su padre.
        // Si no rotamos, 'node' es el mismo, y vamos a su padre.
        if (node->m_parent) {
            node = node->m_parent;
        } else {
            // Si no hay padre, significa que 'node' es la raíz global actual
            newRoot = node;
            break; //Terminamos
        }
    }

    return newRoot;
}
*/

#endif
