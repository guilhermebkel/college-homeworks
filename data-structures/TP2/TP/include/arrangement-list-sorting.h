#ifndef ARRANGEMENT_LIST_SORTING_H
#define ARRANGEMENT_LIST_SORTING_H

#include <iostream>

#include "arrangement-list.h"

template <typename Model> class ArrangementListSorting {
	public:
		ArrangementListSorting(int size);
		void selectionSort(Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE], bool (*compareKeys)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering), ArrangementList<std::string> *lexicographicalOrdering);
	private:
		int size;
};

#endif