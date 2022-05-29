#ifndef ARRANGEMENT_LIST_H
#define ARRANGEMENT_LIST_H

#include <iostream>
#include <string>

#ifndef MAX_ARRANGEMENT_LIST_SIZE 
#define MAX_ARRANGEMENT_LIST_SIZE 1000
#endif

template <typename Model, typename Key> struct Item {
	Model model;
	Key key;
};

template <typename Model, typename Key> class ArrangementList {
	public:
		ArrangementList();
		int getSize();
		void save(Model item, Key key);
		Model find(Key key);

	private:
		Item<Model, Key> itens[MAX_ARRANGEMENT_LIST_SIZE];
		int size;
};

#endif