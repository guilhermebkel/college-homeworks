#include <string.h>
#include <iostream>

#include "poker-face.h"
#include "arrangement-list.h"
#include "shared-util.h"

template <typename Model>
ArrangementList<Model>::ArrangementList () {
	this->size = 0;
};

template <typename Model>
int ArrangementList<Model>::getSize () {
	return this->size;
};

template <typename Model>
void ArrangementList<Model>::update (StringKey key, Model model) {
	int index = this->findIndex(key);

	this->itens[index].model = model;
};

template <typename Model>
void ArrangementList<Model>::update (NumberKey key, Model model) {
	return this->update(castStringKey(key), model);
};

template <typename Model>
void ArrangementList<Model>::create (StringKey key, Model model) {
	Item<Model> item;

	item.model = model;
	item.key = (char*)malloc(MAX_KEY_SIZE * sizeof(char));

	strcpy(item.key, key);

	this->itens[size] = item;

	this->size++;
};

template <typename Model>
void ArrangementList<Model>::create (NumberKey key, Model model) {
	return this->create(castStringKey(key), model);
};

template <typename Model>
Item<Model> ArrangementList<Model>::findByKey (StringKey key) {
	int modelIndex = this->findIndex(key);

	if (!this->existsByIndex(modelIndex)) {
		throw "Model not found";
	}
	
	return this->itens[modelIndex];
};

template <typename Model>
Item<Model> ArrangementList<Model>::findByKey (NumberKey key) {
	return this->findByKey(this->castStringKey(key));
};

template <typename Model>
Item<Model> ArrangementList<Model>::findByIndex (int index) {
	return this->itens[index];
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
bool ArrangementList<Model>::existsByKey (StringKey key) {
	int modelIndex = this->findIndex(key);

	return this->existsByIndex(modelIndex);
};

template <typename Model>
bool ArrangementList<Model>::existsByKey (NumberKey key) {
	this->existsByKey(this->castStringKey(key));
};

template <typename Model>
StringKey ArrangementList<Model>::castStringKey (int number) {
	std::string stringValue = std::to_string(number);

	return castChar(stringValue);
};

template <typename Model>
bool ArrangementList<Model>::existsByIndex (int index) {
	return index != -1;
};

template <typename Model>
void ArrangementList<Model>::sort(SortingType type, int (*getSortingParam)(Model)) {
	for (int i = 0; i < this->getSize(); i++) {
		for (int j = i + 1; j < this->getSize(); j++) {
			int firstItemSortingParam = getSortingParam(this->itens[i].model);
			int secondItemSortingParam = getSortingParam(this->itens[j].model);

			bool canSortDesc = type == SortingType::DESC && firstItemSortingParam < secondItemSortingParam;
			bool canSortAsc = type == SortingType::ASC && firstItemSortingParam > secondItemSortingParam;
			bool canSort = canSortDesc || canSortAsc;

			if (canSort) {
				Item<Model> tempModel = itens[i];

				itens[i] = itens[j];
				itens[j] = tempModel;
			}
		}
	}
};

template class ArrangementList<Round>;
template class ArrangementList<RoundResult>;
template class ArrangementList<Play>;
template class ArrangementList<Balance>;
template class ArrangementList<CardCombo>;
template class ArrangementList<Card>;
