#ifndef QUICK_SORT_UTILS_H
#define QUICK_SORT_UTILS_H

#ifndef MAX_ARRAY_SIZE 
#define MAX_ARRAY_SIZE 10000
#endif

void insertionSort (int left, int right, int itens[], bool (*makeComparison)(int, int));
void quickSortPartition (int left, int right, int *i, int *j, int itens[], bool (*makeComparison)(int, int));
bool mustUseInsertionSortAlgorithm (int left, int right, int quickSortMaxPartitionSize);

#endif