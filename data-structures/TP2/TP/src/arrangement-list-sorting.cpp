#include <iostream>

#include "arrangement-list.h"
#include "arrangement-list-sorting.h"
#include "lexicographic-analyser.h"
#include "memlog.h"
 
void partition(int left, int right, int *i, int *j, int *vector) {
	int x, w;

	*i = left;
	*j = right;

	x = vector[(*i + *j)/2];

	do {
		while (x > vector[*i]) {
			(*i)++;
		}

		while (x < vector[*j]) {
			(*j)--;
		}

		if (*i <= *j) {
			w = vector[*i];
			vector[*i] = vector[*j];
			vector[*j] = w;

			(*i)++;
			(*j)--;
		}

	} while (*i <= *j);
}

void order(int left, int right, int *vector) {
	int i, j;

	partition(left, right, &i, &j, vector);

	if (left < j) {
		order(left, j, vector);
	}

	if (i < right) {
		order(i, right, vector);
	}
}

void quickSort(int *vector, int n) {
	order(0, n-1, vector);
}

template <typename Model>
ArrangementListSorting<Model>::ArrangementListSorting (int size) {
	this->size = size;
};

template <typename Model>
void ArrangementListSorting<Model>::selectionSort(Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*compareKeys)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering), ArrangementList<std::string> *lexicographicalOrdering) {
	for (int i = 0; i < this->size; i++) {
		for (int j = i + 1; j < this->size; j++) {
			LEMEMLOG((long int)(&(itens[i])),sizeof(Model), MemoryLogType::SORT);
			LEMEMLOG((long int)(&(itens[j])),sizeof(Model), MemoryLogType::SORT);

			bool canSort = compareKeys(itens[i].model, itens[j].model, lexicographicalOrdering);

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
