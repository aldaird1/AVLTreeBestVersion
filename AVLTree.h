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


AVLNode* insertRecursive (AVLNode*, int);//Las alturas de los subarboles a los que no se accede no se modifican
void printTreeRecursive (AVLNode*, int);

void insert (AVLNode**, int);
void printTree (AVLNode*);
//======================== DEFINICONES DE LAS FUNCIONES ===================================//
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
    printf ("~~~~> %d\n", node->m_data);

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

AVLNode* insertRecursive (AVLNode* node, int _data) {
    assert (node);
    if (_data > node->m_data) {
        if (node->m_right == NULL) {
            node->m_right = newNode (_data);
            node->m_right->m_parent = node;
            
            node->m_height = 1 + MAX(nodeHeight(node->m_left), nodeHeight(node->m_right));
            return node; //Nunca hacen falta las rotaciones en este caso 
        } else {
            node->m_right = insertRecursive (node->m_right, _data);

            node->m_height = 1 + MAX(nodeHeight(node->m_left), nodeHeight(node->m_right));
            
            //Rotaciones
            return node;//Debe retornar el nuevo root
        }

    } else if (_data < node->m_data) {
        if (node->m_left == NULL) {
            node->m_left = newNode (_data);
            node->m_left->m_parent = node;
            
            node->m_height = 1 + MAX(nodeHeight(node->m_left), nodeHeight(node->m_right));
            return node; //Nunca hacen falta las rotaciones en este caso 
        } else {
            node->m_left = insertRecursive (node->m_left, _data);

            node->m_height = 1 + MAX(nodeHeight(node->m_left), nodeHeight(node->m_right));
            
            //Rotaciones
            return node;//Debe retornar el nuevo root
        }
    } else return node;
}
//



//
void insert (AVLNode** root, int _data) {
    if (*root == NULL)
        *root = newNode (_data);
    else *root = insertRecursive (*root, _data);
}



#endif
