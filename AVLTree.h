#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdio.h>
#include <stdlib.h>

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


//======================== DEFINICONES DE LAS FUNCIONES ===================================//
int nodeHeight (AVLNode* node) {
    if (!node) return -1;
    else return node->m_height;
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

#endif
