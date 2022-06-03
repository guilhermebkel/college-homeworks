#ifndef ARRANGEMENT_LIST_H
#define ARRANGEMENT_LIST_H

#ifndef MAX_ARRANGEMENT_LIST_SIZE 
#define MAX_ARRANGEMENT_LIST_SIZE 1000
#endif

#ifndef MAX_KEY_SIZE 
#define MAX_KEY_SIZE 100
#endif

typedef char *StringKey;
typedef int NumberKey;

enum SortingType {
	ASC = 1,
	DESC = 2
};

template <typename Model> struct Item {
	Model model;
	StringKey key;
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
		void sort(SortingType type, int (*func)(Model));

	private:
		Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE];
		int size;
		int findIndex(StringKey key);
		int findIndex(NumberKey key);
		StringKey castStringKey (NumberKey numberKey);
		bool existsByIndex (int index);
};

#endif