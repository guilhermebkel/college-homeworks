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
void ArrangementListSorting<Model>::quickSortPartition(int left, int right, int *i, int *j, Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*makeComparison)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering)) {
	Item<Model> x, w;

	*i = left;
	*j = right;
	
	bool isFirstPartition = left == 0 && right == this->size - 1;
	bool customPivotExists = this->quickSortPivot != -1;
	bool canUseCustomPivot = isFirstPartition && customPivotExists;

	if (canUseCustomPivot) {
		x = itens[this->quickSortPivot];
	} else {
		x = itens[(*i + *j)/2];
	}

	do {
		while (makeComparison(x.model, itens[*i].model, this->lexicographicalOrdering)) {
			LEMEMLOG((long int)(&(itens[*i])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_QUICK_SORT);

			(*i)++;
		}

		while (makeComparison(itens[*j].model, x.model, this->lexicographicalOrdering)) {
			LEMEMLOG((long int)(&(itens[*j])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_QUICK_SORT);

			(*j)--;
		}

		if (*i <= *j) {
			w = itens[*i];
			itens[*i] = itens[*j];
			itens[*j] = w;

			ESCREVEMEMLOG((long int)(&(itens[*i])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_QUICK_SORT);
			ESCREVEMEMLOG((long int)(&(itens[*j])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_QUICK_SORT);

			(*i)++;
			(*j)--;
		}
	} while (*i <= *j);
};

template <typename Model>
void ArrangementListSorting<Model>::quickSortOrder(int left, int right, Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*makeComparison)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering)) {
	int i, j;

	int currentPartitionSize = right - left;

	bool maxPartitionSizeExists = this->quickSortMaxPartitionSize != -1;
	bool isCurrentPartitionSizeOverMaxValue = currentPartitionSize > this->quickSortMaxPartitionSize;
	bool mustUseSimpleSortingAlgorithm = maxPartitionSizeExists && isCurrentPartitionSizeOverMaxValue;

	if (mustUseSimpleSortingAlgorithm) {
		this->selectionSort(left, right + 1, itens, makeComparison);
	} else {
		this->quickSortPartition(left, right, &i, &j, itens, makeComparison);

		if (left < j) {
			this->quickSortOrder(left, j, itens, makeComparison);
		}

		if (i < right) {
			this->quickSortOrder(i, right, itens, makeComparison);
		}
	}
};

template <typename Model>
void ArrangementListSorting<Model>::quickSort(Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*makeComparison)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering)) {
	this->quickSortOrder(0, this->size - 1, itens, makeComparison);
};

template <typename Model>
void ArrangementListSorting<Model>::selectionSort(int left, int right, Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*makeComparison)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering)) {
	for (int i = left; i < right; i++) {
		for (int j = i + 1; j < right; j++) {
			LEMEMLOG((long int)(&(itens[i])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_SELECTION_SORT);
			LEMEMLOG((long int)(&(itens[j])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_SELECTION_SORT);

			bool canSort = makeComparison(itens[i].model, itens[j].model, this->lexicographicalOrdering);

			if (canSort) {
				Item<Model> tempModel = itens[i];

				itens[i] = itens[j];
				itens[j] = tempModel;

				ESCREVEMEMLOG((long int)(&(itens[i])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_SELECTION_SORT);
				ESCREVEMEMLOG((long int)(&(itens[j])),sizeof(Item<Model>), MemoryLogType::ARRANGEMENT_LIST_SELECTION_SORT);
			}
		}
	}
};

template class ArrangementListSorting<WordOccurence>;
template class ArrangementListSorting<std::string>;
