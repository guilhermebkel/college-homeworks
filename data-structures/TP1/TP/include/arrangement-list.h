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

template <typename Model> struct Item {
	Model model;
	StringKey key;
};

template <typename Model> class ArrangementList {
	public:
		ArrangementList();
		int getSize();
		void save(StringKey key, Model item);
		void save(NumberKey key, Model item);
		Model find(StringKey key);
		Model find(NumberKey key);
		bool exists(StringKey key);
		bool exists(NumberKey key);
		Model get(int index);

	private:
		Item<Model> itens[MAX_ARRANGEMENT_LIST_SIZE];
		int size;
		int findIndex(StringKey key);
		int findIndex(NumberKey key);
		StringKey castStringKey (NumberKey numberKey);
		bool existsByIndex (int index);
};

#endif