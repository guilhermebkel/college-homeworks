#include <iostream>
#include <string.h>
 
#include "arrangement-list.h"

template <typename Model, typename Key>
ArrangementList<Model, Key>::ArrangementList () {
	this->size = -1;
};

template <typename Model, typename Key>
int ArrangementList<Model, Key>::getSize () {
	return this->size;
};

template <typename Model, typename Key>
void ArrangementList<Model, Key>::save (Model model, Key key) {
	this->size++;

	Item<Model, Key> item;

	item.model = model;
	item.key = key;

	this->itens[size] = item;
};

template <typename Model, typename Key>
Model ArrangementList<Model, Key>::find (Key key) {
	for (int index = 0; index < this->size; index++) {
		Item<Model, Key> foundItem = this->itens[index];

		if (foundItem.key == key) {
			return foundItem.model;
		}
	}
};
