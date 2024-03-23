#ifndef RECURSIVE_QUICK_SORT_H
#define RECURSIVE_QUICK_SORT_H

#ifndef MAX_ARRAY_SIZE 
#define MAX_ARRAY_SIZE 200
#endif

template <typename Model>
void quickSortPartition(int left, int right, int *i, int *j, Model itens[], int quickSortPivot, int size, bool (*makeComparison)(Model, Model));

#endif