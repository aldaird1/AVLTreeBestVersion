#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef AVLTREE_H
#define AVLTREE_H

#define MAX(a,b) ((a>b)?a:b)

typedef struct AVLNode {
    int m_height;
    int m_data; 
    struct AVLNode* m_left;
    struct AVLNode* m_right;
    struct AVLNode* m_parent;
}AVLNode;

AVLNode* newNode (int); 
int bf (AVLNode* );
int nodeHeight (AVLNode*);
AVLNode* leftRotate (AVLNode*);
AVLNode* rightRotate (AVLNode*);
AVLNode* rebalancing (AVLNode*);
AVLNode* insertIt (AVLNode*, int);
void printTreeRecursive (AVLNode*, int);
void insert (AVLNode**, int);
void printTree (AVLNode*);

#endif
