#include "AVLTree.h"

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

int bf (AVLNode* node) {
	return nodeHeight (node->m_right) - nodeHeight (node->m_left);	
}

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

void insert (AVLNode** root, int _data) {
	if (!(*root)) {
		*root = insertIt (*root, _data);
		return;
	}

	AVLNode* last = insertIt (*root, _data);
	*root = rebalancing (last);
}
