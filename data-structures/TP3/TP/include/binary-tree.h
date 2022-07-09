#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

template <typename Model> struct Item {
	Model model;
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
		Item<Model> remove(int key);
		Node<Model> *getRoot();

	private:
		void recursiveInsert(Node<Model>* &node, Item<Model> item);
		void recursiveDelete(Node<Model>* node);
		Item<Model> recursiveSearch(Node<Model> *node, int key);
		Node<Model> *root;
};

#endif