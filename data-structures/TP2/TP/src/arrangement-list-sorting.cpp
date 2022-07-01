#include <iostream>

#include "arrangement-list.h"
#include "arrangement-list-sorting.h"
#include "lexicographic-analyser.h"
#include "memlog.h"

template <typename Model>
ArrangementListSorting<Model>::ArrangementListSorting (int size, ArrangementList<std::string> *lexicographicalOrdering, int quickSortPivot, int quickSortMaxPartitionSize) {
	this->lexicographicalOrdering = lexicographicalOrdering;

	this->size = size;

	this->quickSortPivot = quickSortPivot;
	this->quickSortMaxPartitionSize = quickSortMaxPartitionSize;
};

template <typename Model>
void ArrangementListSorting<Model>::quickSortPartition(int left, int right, int *i, int *j, Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*compareKeys)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering)) {
	Item<Model> x, w;

	*i = left;
	*j = right;
	
	bool isFirstPartition = left == 0 || right == this->size - 1;

	if (isFirstPartition && this->quickSortPivot != -1) {
		x = itens[this->quickSortPivot];
	} else {
		x = itens[(*i + *j)/2];
	}

	do {
		while (compareKeys(x.model, itens[*i].model, this->lexicographicalOrdering)) {
			(*i)++;
		}

		while (compareKeys(itens[*j].model, x.model, this->lexicographicalOrdering)) {
			(*j)--;
		}

		if (*i <= *j) {
			w = itens[*i];
			itens[*i] = itens[*j];
			itens[*j] = w;

			(*i)++;
			(*j)--;
		}
	} while (*i <= *j);
};

template <typename Model>
void ArrangementListSorting<Model>::quickSortOrder(int left, int right, Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*compareKeys)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering)) {
	int i, j;

	this->quickSortPartition(left, right, &i, &j, itens, compareKeys);

	if (left < j) {
		this->quickSortOrder(left, j, itens, compareKeys);
	}

	if (i < right) {
		this->quickSortOrder(i, right, itens, compareKeys);
	}
};

template <typename Model>
void ArrangementListSorting<Model>::quickSort(Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*compareKeys)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering)) {
	this->quickSortOrder(0, this->size - 1, itens, compareKeys);
};

template <typename Model>
void ArrangementListSorting<Model>::selectionSort(Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*compareKeys)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering)) {
	for (int i = 0; i < this->size; i++) {
		for (int j = i + 1; j < this->size; j++) {
			LEMEMLOG((long int)(&(itens[i])),sizeof(Model), MemoryLogType::SORT);
			LEMEMLOG((long int)(&(itens[j])),sizeof(Model), MemoryLogType::SORT);

			bool canSort = compareKeys(itens[i].model, itens[j].model, this->lexicographicalOrdering);

			if (canSort) {
				Item<Model> tempModel = itens[i];

				itens[i] = itens[j];
				itens[j] = tempModel;

				ESCREVEMEMLOG((long int)(&(itens[i])),sizeof(Model), MemoryLogType::SORT);
				ESCREVEMEMLOG((long int)(&(itens[j])),sizeof(Model), MemoryLogType::SORT);
			}
		}
	}
};

template class ArrangementListSorting<WordOccurence>;
template class ArrangementListSorting<std::string>;
