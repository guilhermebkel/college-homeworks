#ifndef ARRANGEMENT_LIST_SORTING_H
#define ARRANGEMENT_LIST_SORTING_H

#include <iostream>

#include "arrangement-list.h"

template <typename Model> class ArrangementListSorting {
	public:
		ArrangementListSorting(int size, ArrangementList<std::string> *lexicographicalOrdering, int quickSortPivot, int quickSortMaxPartitionSize);
		void quickSort(Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*makeComparison)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering));
	private:
		int size;
		ArrangementList<std::string> *lexicographicalOrdering;
		int quickSortPivot;
		int quickSortMaxPartitionSize;
		void selectionSort(int left, int right, Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*makeComparison)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering));
		void quickSortOrder(int left, int right, Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*makeComparison)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering));
		void quickSortPartition(int left, int right, int *i, int *j, Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*makeComparison)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering));
};

#endif