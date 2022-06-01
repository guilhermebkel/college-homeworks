#include <iostream>
#include <string.h>
#include <limits.h>

#include "poker-face.h"
#include "arrangement-list.h"

template <typename Model>
ArrangementList<Model>::ArrangementList () {
	this->size = 0;
};

template <typename Model>
int ArrangementList<Model>::getSize () {
	return this->size;
};

template <typename Model>
void ArrangementList<Model>::save (StringKey key, Model model) {
	int existingModelIndex = this->findIndex(key);

	if (this->existsByIndex(existingModelIndex)) {
		this->itens[existingModelIndex].model = model;
	} else {
		Item<Model> item;

		item.model = model;
		item.key = (char*)malloc(MAX_KEY_SIZE * sizeof(char));

		strcpy(item.key, key);

		this->itens[size] = item;

		this->size++;
	}
};

template <typename Model>
void ArrangementList<Model>::save (NumberKey key, Model model) {
	int existingModelIndex = this->findIndex(key);

	if (this->existsByIndex(existingModelIndex)) {
		this->itens[existingModelIndex].model = model;
	} else {
		Item<Model> item;

		item.model = model;
		item.key = this->castStringKey(key);

		this->itens[size] = item;

		this->size++;
	}
};

template <typename Model>
Model ArrangementList<Model>::find (StringKey key) {
	int modelIndex = this->findIndex(key);

	if (!this->existsByIndex(modelIndex)) {
		throw "Model not found";
	}
	
	return this->itens[modelIndex].model;
};

template <typename Model>
Model ArrangementList<Model>::find (NumberKey key) {
	return this->find(this->castStringKey(key));
};

template <typename Model>
Model ArrangementList<Model>::get (int index) {
	return this->itens[index].model;
};

template <typename Model>
int ArrangementList<Model>::findIndex (StringKey key) {
	for (int index = 0; index < this->size; index++) {
		Item<Model> foundItem = this->itens[index];

		bool foundKey = strcmp(foundItem.key, key) == 0;

		if (foundKey) {
			return index;
		}
	}

	return -1;
};

template <typename Model>
int ArrangementList<Model>::findIndex (NumberKey key) {
	this->findIndex(this->castStringKey(key));
};

template <typename Model>
bool ArrangementList<Model>::exists (StringKey key) {
	int modelIndex = this->findIndex(key);

	return this->existsByIndex(modelIndex);
};

template <typename Model>
bool ArrangementList<Model>::exists (NumberKey key) {
	this->exists(this->castStringKey(key));
};

template <typename Model>
StringKey ArrangementList<Model>::castStringKey (int number) {
	std::string stringValue = std::to_string(number);

	StringKey charValue = new char[stringValue.length()];

	strcpy(charValue, stringValue.c_str());

	return charValue;
};

template <typename Model>
bool ArrangementList<Model>::existsByIndex (int index) {
	return index != -1;
};

template class ArrangementList<Round>;
template class ArrangementList<RoundResult>;
template class ArrangementList<Play>;
template class ArrangementList<Balance>;
