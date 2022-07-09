#include <iostream>
#include <string.h>

#include "binary-tree.h"
#include "mailer.h"
#include "binary-tree-validation.h"

template <typename Model>
Node<Model>::Node(Item<Model> item) {
	this->item = item;
};

template <typename Model>
Item<Model> Node<Model>::getItem() {
	return this->item;
};

template <typename Model>
Node<Model> *Node<Model>::getLeft() {
	return this->left;
};

template <typename Model>
Node<Model> *Node<Model>::getRight() {
	return this->right;
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
	this->recursiveInsert(root, item);
};

template <typename Model>
void BinaryTree<Model>::clear() {
	this->recursiveDelete(root);

	this->root = NULL;
};

template <typename Model>
Item<Model> BinaryTree<Model>::search(int key) {
	return this->recursiveSearch(root, key);
};

template <typename Model>
Item<Model> BinaryTree<Model>::remove(int key) {
	Node<Model> node = this->search(key);

	Item<Model> item;

	if (isValidNodeItem(node.getItem())) {
		item = node.getItem();

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
void BinaryTree<Model>::recursiveInsert(Node<Model>* node, Item<Model> item) {
	if(node == NULL) {
		node = new Node<Model>(item);
	} else {
		if (item.key < node->getItem().key) {
			this->recursiveInsert(node->getLeft(), item);
		} else {
			this->recursiveInsert(node->getRight(), item);
		}
	}
};

template <typename Model>
void BinaryTree<Model>::recursiveDelete(Node<Model>* node) {
	if(node != NULL){
		this->recursiveDelete(node->getLeft());
		this->recursiveDelete(node->getRight());

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

	if (key < node->getItem().key) {
		return this->recursiveSearch(node->getLeft(), key);
	} else if (key > node->getItem().key) {
		return this->recursiveSearch(node->getRight(), key);
	} else {
		return node->getItem();
	}
};

template class BinaryTree<Message>;
