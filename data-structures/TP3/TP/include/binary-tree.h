#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

template <typename Model> struct Item {
	Model *model;
	int key;
};

template <typename Model> class Node {
	public:
		Node(Item<Model> item);
		Item<Model> item;
		Node<Model> *left;
		Node<Model> *right;
};

template <typename Model> class BinaryTree {
  public:
		BinaryTree();
		~BinaryTree();
		void insert(Item<Model> item);
		void clear();
		Item<Model> search(int key);
		void remove(int key);

	private:
		void recursiveInsert(Node<Model>* &node, Item<Model> item);
		void recursiveDelete(Node<Model>* &node, int key);
		void deleteNode (Node<Model>* node, Node<Model>* &antecessor);
		Node<Model> *recursiveSearch(Node<Model> *node, int key);
		Node<Model> *findNode(int key);
		Node<Model> *root;
};

#endif