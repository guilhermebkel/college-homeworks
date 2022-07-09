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
	this->recursiveDelete(this->root);

	this->root = NULL;
};

template <typename Model>
Item<Model> BinaryTree<Model>::search(int key) {
	return this->recursiveSearch(this->root, key);
};

template <typename Model>
Item<Model> BinaryTree<Model>::remove(int key) {
	Node<Model> node = this->search(key);

	Item<Model> item;

	if (isValidNodeItem(node.item)) {
		item = node.item;

		// delete node;
	} else {
		item.key = -1;
	}

	return item;
};

template <typename Model>
Node<Model> *BinaryTree<Model>::getRoot() {
	return this->root;
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
void BinaryTree<Model>::recursiveDelete(Node<Model>* node) {
	if(node != NULL){
		this->recursiveDelete(node->left);
		this->recursiveDelete(node->right);

		delete node;
	}
};

template <typename Model>
Item<Model> BinaryTree<Model>::recursiveSearch(Node<Model> *node, int key) {
	Item<Model> aux;

	if (node == NULL) {
		aux.key = -1;

		return aux;
	}

	if (key < node->item.key) {
		return this->recursiveSearch(node->left, key);
	} else if (key > node->item.key) {
		return this->recursiveSearch(node->right, key);
	} else {
		return node->item;
	}
};

template class BinaryTree<Message>;
