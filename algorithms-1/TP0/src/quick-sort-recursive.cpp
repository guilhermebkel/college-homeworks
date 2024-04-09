#include <iostream>
#include "quick-sort-utils.hpp"

void quickSortRecursiveOrder (int left, int right, int itens[MAX_ARRAY_SIZE], int quickSortMaxPartitionSize, bool (*makeComparison)(int, int)) {
    if (mustUseInsertionSortAlgorithm(left, right, quickSortMaxPartitionSize)) {
        insertionSort(left, right + 1, itens, makeComparison);
    } else {
        int i, j;

        quickSortPartition(left, right, &i, &j, itens, makeComparison);

        if (left < j) {
            quickSortRecursiveOrder(left, j, itens, quickSortMaxPartitionSize, makeComparison);
        }

        if (i < right) {
            quickSortRecursiveOrder(i, right, itens, quickSortMaxPartitionSize, makeComparison);
        }
    }
}

void quickSortRecursive (int itens[MAX_ARRAY_SIZE], int size, int quickSortMaxPartitionSize, bool (*makeComparison)(int, int)) {
    quickSortRecursiveOrder(0, size - 1, itens, quickSortMaxPartitionSize, makeComparison);
}
