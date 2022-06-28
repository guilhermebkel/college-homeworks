#include <string.h>
#include <iostream>

#include "arrangement-list.h"
#include "lexicographic-analyser.h"
#include "shared-util.h"
#include "memlog.h"

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
	int index = this->findIndex(key, MemoryLogType::UPDATE);

	this->itens[index].model = model;

	ESCREVEMEMLOG((long int)(&(this->itens[index])),sizeof(Model), MemoryLogType::UPDATE);
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

	ESCREVEMEMLOG((long int)(&(this->itens[size])),sizeof(Model), MemoryLogType::CREATE);

	this->size++;
};

template <typename Model>
void ArrangementList<Model>::create (NumberKey key, Model model) {
	return this->create(castStringKey(key), model);
};

template <typename Model>
Item<Model> ArrangementList<Model>::findByKey (StringKey key) {
	int modelIndex = this->findIndex(key, MemoryLogType::FIND);

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
	LEMEMLOG((long int)(&(this->itens[index])),sizeof(Model), MemoryLogType::FIND);

	return this->itens[index];
};

template <typename Model>
int ArrangementList<Model>::findIndex (StringKey key, MemoryLogType memoryLogType) {
	for (int index = 0; index < this->size; index++) {
		Item<Model> foundItem = this->itens[index];

		LEMEMLOG((long int)(&(this->itens[index])),sizeof(Model), memoryLogType);

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
	int modelIndex = this->findIndex(key, MemoryLogType::FIND);

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
void ArrangementList<Model>::sort(CompareKeys<Model> compareKeys) {
	for (int i = 0; i < this->getSize(); i++) {
		for (int j = i + 1; j < this->getSize(); j++) {
			LEMEMLOG((long int)(&(this->itens[i])),sizeof(Model), MemoryLogType::SORT);
			LEMEMLOG((long int)(&(this->itens[j])),sizeof(Model), MemoryLogType::SORT);

			bool canSort = compareKeys(this->itens[i].model, this->itens[j].model);

			if (canSort) {
				Item<Model> tempModel = this->itens[i];

				this->itens[i] = itens[j];
				this->itens[j] = tempModel;

				ESCREVEMEMLOG((long int)(&(this->itens[i])),sizeof(Model), MemoryLogType::SORT);
				ESCREVEMEMLOG((long int)(&(this->itens[j])),sizeof(Model), MemoryLogType::SORT);
			}
		}
	}
};

template class ArrangementList<WordOccurence>;
template class ArrangementList<std::string>;
