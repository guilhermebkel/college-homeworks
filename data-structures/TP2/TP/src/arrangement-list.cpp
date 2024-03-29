#include <string.h>
#include <iostream>

#include "arrangement-list.h"
#include "arrangement-list-sorting.h"
#include "lexicographic-analyser.h"
#include "shared-util.h"
#include "memlog.h"
#include "app-memlog.h"

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
	int index = this->findIndex(key, MemoryLogType::ARRANGEMENT_LIST_UPDATE);

	this->itens[index].model = model;

	ESCREVEMEMLOG((long int)(&(this->itens[index])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_UPDATE);
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
	item.index = size;

	strcpy(item.key, key);

	this->itens[size] = item;

	ESCREVEMEMLOG((long int)(&(this->itens[size])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_CREATE);

	this->size++;
};

template <typename Model>
void ArrangementList<Model>::create (NumberKey key, Model model) {
	return this->create(castStringKey(key), model);
};

template <typename Model>
Item<Model> ArrangementList<Model>::findByKey (StringKey key) {
	int modelIndex = this->findIndex(key, MemoryLogType::ARRANGEMENT_LIST_FIND);

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
	LEMEMLOG((long int)(&(this->itens[index])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_FIND);

	return this->itens[index];
};

template <typename Model>
int ArrangementList<Model>::findIndex (StringKey key, MemoryLogType memoryLogType) {
	for (int index = 0; index < this->size; index++) {
		Item<Model> foundItem = this->itens[index];

		LEMEMLOG((long int)(&(this->itens[index])),sizeof(Item<Model>), memoryLogType);

		bool foundKey = strcmp(foundItem.key, key) == 0;

		if (foundKey) {
			return index;
		}
	}

	return -1;
};

template <typename Model>
int ArrangementList<Model>::findIndex (NumberKey key, MemoryLogType memoryLogType) {
	this->findIndex(this->castStringKey(key), memoryLogType);
};

template <typename Model>
bool ArrangementList<Model>::existsByKey (StringKey key) {
	int modelIndex = this->findIndex(key, MemoryLogType::ARRANGEMENT_LIST_FIND);

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
void ArrangementList<Model>::sort(bool (*makeComparison)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering), ArrangementList<std::string> *lexicographicalOrdering, int quickSortPivot, int quickSortMaxPartitionSize) {
	ArrangementListSorting<Model> *arrangementListSorting = new ArrangementListSorting<Model>(this->getSize(), lexicographicalOrdering, quickSortPivot, quickSortMaxPartitionSize);

	return arrangementListSorting->quickSort(this->itens, makeComparison);
};

template class ArrangementList<WordOccurence>;
template class ArrangementList<std::string>;
