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
int nodeHeight (AVLNode*);
void leftRotate (AVLNode*);
void rightRotate (AVLNode*);
void rebalancing (AVLNode*);

AVLNode* insertIt (AVLNode*, int);//Las alturas de los subarboles a los que no se accede no se modifican
void printTreeRecursive (AVLNode*, int);

void insert (AVLNode**, int);
void printTree (AVLNode*);
//======================== DEFINICONES DE LAS FUNCIONES ===================================//

void rightRotate (AVLNode* node) {
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
}

void leftRotate (AVLNode* node) {
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
    printf ("---- %d\n", node->m_data);

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
        *root = insertIt (*root,_data);
        return;
    }

    AVLNode* last = insertIt (*root, _data);
    //rebalancing (last); 
}




#endif
