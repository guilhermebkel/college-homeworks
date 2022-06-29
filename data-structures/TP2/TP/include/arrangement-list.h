#ifndef ARRANGEMENT_LIST_H
#define ARRANGEMENT_LIST_H

#ifndef MAX_ARRANGEMENT_LIST_SIZE 
#define MAX_ARRANGEMENT_LIST_SIZE 10000
#endif

#ifndef MAX_KEY_SIZE 
#define MAX_KEY_SIZE 200
#endif

#include <iostream>
#include <functional>

typedef char *StringKey;
typedef int NumberKey;
typedef char LexicographicalOrdering[100];

enum MemoryLogType {
	UPDATE = 0,
	CREATE = 1,
	FIND = 2,
	SORT = 3
};

template <typename Model> struct Item {
	Model model;
	StringKey key;
	int index;
};

template <typename Model> class ArrangementList {
	public:
		ArrangementList();
		int getSize();
		void create(StringKey key, Model item);
		void create(NumberKey key, Model item);
		void update(StringKey key, Model item);
		void update(NumberKey key, Model item);
		Item<Model> findByKey(StringKey key);
		Item<Model> findByKey(NumberKey key);
		bool existsByKey(StringKey key);
		bool existsByKey(NumberKey key);
		Item<Model> findByIndex(int index);
		void sort(bool (*compareKeys)(Model, Model, ArrangementList<std::string> *lexicographicalOrdering), ArrangementList<std::string> *lexicographicalOrdering);

	private:
		Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE];
		int size;
		int findIndex(StringKey key, MemoryLogType memoryLogType);
		int findIndex(NumberKey key, MemoryLogType memoryLogType);
		StringKey castStringKey (NumberKey numberKey);
		bool existsByIndex (int index);
};

#endif