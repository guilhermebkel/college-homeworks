#include <iostream>
#include <string.h>

#include "hash-table.h"
#include "mailer.h"

template <typename Model>
HashTable<Model>::HashTable(int size) {
	this->size = size;
};

template <typename Model>
Item<Model> HashTable<Model>::search(int primaryKey, int foreignKey) {
	int index = this->hash(primaryKey);

	Item<Model> item = this->table[index].search(foreignKey);

	return item;
};

template <typename Model>
int HashTable<Model>::insert(int primaryKey, Item<Model> item) {
	int index = this->hash(primaryKey);

	this->table[index].insert(item);

	return index;
};

template <typename Model>
void HashTable<Model>::remove(int primaryKey, int foreignKey) {
	int index = this->hash(primaryKey);

	this->table[index].remove(foreignKey);
};

template <typename Model>
int HashTable<Model>::hash(int primaryKey) {
	return primaryKey % this->size;
};

template class HashTable<Message>;
