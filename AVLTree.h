#ifndef AVLTREE_H
#define AVLTREE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) ((a>=b)?a:b)

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
void printTreeRecursive (AVLNode*, int);
AVLNode* insertRecursive (AVLNode*, int);//Las alturas de los subarboles a los que no se accede no se modifica  
AVLNode* leftRotate (AVLNode*);
AVLNode* rightRotate ( AVLNode*);

void insert (AVLNode**, int);

//======================== DEFINICONES DE LAS FUNCIONES ===================================//
int bf (AVLNode* node) {
    if (!node) return 0;
    int balanceFactor = nodeHeight (node->m_right) - nodeHeight (node->m_left);
    return balanceFactor;
}

AVLNode* rightRotate (AVLNode* node) {
    assert (node);
    assert (node->m_left);
    if (node->m_parent == NULL) {
        AVLNode* nuevo = node->m_left;
        AVLNode* back = nuevo->m_right;

        nuevo->m_parent = NULL;
        nuevo->m_right = node; 
        node->m_parent = nuevo;
        node->m_left = back;
        if (back) back->m_parent = node;

        nuevo->m_height = 1 + MAX(nodeHeight (nuevo->m_left), nodeHeight (nuevo->m_right));
        node->m_height = 1 + MAX(nodeHeight (node->m_left), nodeHeight (node->m_right));

        return nuevo;

    } else {
        AVLNode* nuevo = node->m_left;
        AVLNode* back = nuevo->m_right;

        nuevo->m_parent = node->m_parent;
        if (node == nuevo->m_parent->m_left) {
            nuevo->m_parent->m_left = nuevo;
        } else {
            nuevo->m_parent->m_right = nuevo;
        }

        nuevo->m_right = node;
        node->m_parent = nuevo;
        node->m_right = back;
        if (back) back->m_parent = node;
        
        nuevo->m_height = 1 + MAX(nodeHeight (nuevo->m_left), nodeHeight (nuevo->m_right));
        node->m_height = 1 + MAX(nodeHeight (node->m_left), nodeHeight (node->m_right));

        return nuevo;
    }
}

AVLNode* leftRotate (AVLNode* node) {
    assert (node);
    assert (node->m_right);
    if (node->m_parent == NULL) {
        AVLNode* nuevo = node->m_right;
        AVLNode* back = nuevo->m_left;

        nuevo->m_parent = NULL;
        nuevo->m_left = node; 
        node->m_parent = nuevo;
        node->m_right = back;
        if (back) back->m_parent = node;

        nuevo->m_height = 1 + MAX(nodeHeight (nuevo->m_left), nodeHeight (nuevo->m_right));
        node->m_height = 1 + MAX(nodeHeight (node->m_left), nodeHeight (node->m_right));

        return nuevo;

    } else {
        AVLNode* nuevo = node->m_right;
        AVLNode* back = nuevo->m_left;

        nuevo->m_parent = node->m_parent;
        if (node == nuevo->m_parent->m_left) {
            nuevo->m_parent->m_left = nuevo;
        } else {
            nuevo->m_parent->m_right = nuevo;
        }

        nuevo->m_left = node;
        node->m_parent = nuevo;
        node->m_right = back;
        if (back) back->m_parent = node;
        
        nuevo->m_height = 1 + MAX(nodeHeight (nuevo->m_left), nodeHeight (nuevo->m_right));
        node->m_height = 1 + MAX(nodeHeight (node->m_left), nodeHeight (node->m_right));

        return nuevo;
    }
}

void printTreeRecursive (AVLNode* node, int sub) {
    if (!node) return;
    printTreeRecursive (node->m_right, sub + 1);
    
    for (int i = 1; i < sub; i++) {
        printf ("      ");
    }
    printf ("------%d\n", node->m_data);

    printTreeRecursive (node->m_left, sub + 1);
    return;
}

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

            int bfa = bf (node);
            int bfr = bf (node->m_right);
            int bfl = bf (node->m_left);

            if (bfa == 2 && bfl == -1) {
                node->m_right = rightRotate (node->m_right);
                node = leftRotate (node);
                return node;
            } else if (bfa == -2  && bfr == 1) {
                node->m_left = leftRotate (node->m_left);
                node = rightRotate (node);
                return node;
            } else if (bfa == -2) {
                node = rightRotate (node);
                return node;
            } else if (bfa == 2) {
                node = leftRotate (node);
                return node;
            } else {
                return node;
            }
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

            int bfa = bf (node);
            int bfr = bf (node->m_right);
            int bfl = bf (node->m_left);

            if (bfa == 2 && bfl == -1) {
                node->m_right = rightRotate (node->m_right);
                node = leftRotate (node);
                return node;
            } else if (bfa == -2  && bfr == 1) {
                node->m_left = leftRotate (node->m_left);
                node = rightRotate (node);
                return node;
            } else if (bfa == -2) {
                node = rightRotate (node);
                return node;
            } else if (bfa == 2) {
                node = leftRotate (node);
                return node;
            } else {
                return node;
            }
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
