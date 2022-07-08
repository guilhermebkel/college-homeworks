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
		Item<Model> getItem ();
		Node<Model> *getLeft ();
		Node<Model> *getRight ();

	private:
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
		Node<Model> *getRoot();

	private:
		void recursiveInsert(Node<Model>* &node, Item<Model> item);
		void recursiveDelete(Node<Model>* node);
		Node<Model> *root;
};

#endif