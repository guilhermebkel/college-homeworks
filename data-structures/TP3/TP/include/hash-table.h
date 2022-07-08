#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

#include "binary-tree.h"

template <typename Model> class HashTable {
  public:
    HashTable(int size);

	private:
		BinaryTree<Model> hashTable[1000];
};

#endif