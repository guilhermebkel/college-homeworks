#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

#include "binary-tree.h"

template <typename Model> class HashTable {
  public:
    HashTable(int size);
		Item<Model> search(int primaryKey, int foreignKey);
		int insert(int primaryKey, Item<Model> item);
		void remove(int primaryKey, int foreignKey);

	private:
		BinaryTree<Model> table[1000];
		int hash(int primaryKey);
		int size;
};

#endif