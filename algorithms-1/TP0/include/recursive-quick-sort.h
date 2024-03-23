#ifndef RECURSIVE_QUICK_SORT_H
#define RECURSIVE_QUICK_SORT_H

#ifndef MAX_ARRAY_SIZE 
#define MAX_ARRAY_SIZE 200
#endif

template <typename Model>
struct Item {
    Model model;
};

template <typename Model>
void quickSort(Model itens[], int size, int quickSortMaxPartitionSize, bool (*makeComparison)(Model, Model));

#endif