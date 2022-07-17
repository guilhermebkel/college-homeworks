#include <iostream>
#include <string.h>

#include "binary-tree.h"
#include "mailer.h"
#include "binary-tree-validation.h"

template <typename Model>
Node<Model>::Node(Item<Model> item) {
	this->item = item;

	this->left = NULL;
	this->right = NULL;
};

template <typename Model>
BinaryTree<Model>::BinaryTree() {
	this->root = NULL;
};

template <typename Model>
BinaryTree<Model>::~BinaryTree() {
	this->clear();
};

template <typename Model>
void BinaryTree<Model>::insert(Item<Model> item) {
	this->recursiveInsert(this->root, item);
};

template <typename Model>
void BinaryTree<Model>::clear() {
	this->recursiveDelete(this->root, this->root->item.key);

	this->root = NULL;
};

template <typename Model>
Item<Model> BinaryTree<Model>::search(int key) {
	Node<Model> *node = this->recursiveSearch(this->root, key);

	return node->item;
};

template <typename Model>
Node<Model> *BinaryTree<Model>::findNode(int key) {
	return this->recursiveSearch(this->root, key);
};

template <typename Model>
void BinaryTree<Model>::remove(int key) {
	this->recursiveDelete(this->root, key);
};

template <typename Model>
void BinaryTree<Model>::recursiveInsert(Node<Model>* &node, Item<Model> item) {
	if(node == NULL) {
		node = new Node<Model>(item);
	} else {
		if (item.key < node->item.key) {
			this->recursiveInsert(node->left, item);
		} else {
			this->recursiveInsert(node->right, item);
		}
	}
};

template <typename Model>
void BinaryTree<Model>::deleteNode(Node<Model>* node, Node<Model>* &antecessor) {
	if(antecessor->right != NULL) {
		this->deleteNode(node, antecessor->right);

		return;
	}

	node->item = antecessor->item;
	node = antecessor;
	antecessor = antecessor->left;

	free(node);
};

template <typename Model>
void BinaryTree<Model>::recursiveDelete(Node<Model>* &node, int key) {
	if (node == NULL) {
		return;
	}

	if (key < node->item.key) {
		return recursiveDelete(node->left, key);
	} else if (key > node->item.key) {
		return recursiveDelete(node->right, key);
	} else {
		Node<Model> *aux;

		if (node->right == NULL) {
			aux = node;
			node = node->left;
			free(aux);
		} else if(node->left == NULL) {
			aux = node;
			node = node->right;
			free(aux);
		} else {
			this->deleteNode(node, node->left);
		}
	}
};

template <typename Model>
Node<Model> *BinaryTree<Model>::recursiveSearch(Node<Model> *node, int key) {
	if (node == NULL) {
		Item<Model> mockedItem;
		mockedItem.key = -1;

		Node<Model> *mockedNode = new Node<Model>(mockedItem);

		return mockedNode;
	}

	if (key < node->item.key) {
		return this->recursiveSearch(node->left, key);
	} else if (key > node->item.key) {
		return this->recursiveSearch(node->right, key);
	} else {
		return node;
	}
};

template class BinaryTree<Message>;
