#include <iostream>
#include "quick-sort-utils.h"

void quickSortRecursiveOrder (int left, int right, int itens[MAX_ARRAY_SIZE], int quickSortMaxPartitionSize, int size, bool (*makeComparison)(int, int)) {
    if (mustUseInsertionSortAlgorithm(left, right, quickSortMaxPartitionSize)) {
        insertionSort(left, right + 1, itens, makeComparison);
    } else {
        int i, j;

        quickSortPartition(left, right, &i, &j, itens, -1, size, makeComparison);

        if (left < j) {
            quickSortRecursiveOrder(left, j, itens, quickSortMaxPartitionSize, size, makeComparison);
        }

        if (i < right) {
            quickSortRecursiveOrder(i, right, itens, quickSortMaxPartitionSize, size, makeComparison);
        }
    }
}

void quickSortRecursive (int itens[MAX_ARRAY_SIZE], int size, int quickSortMaxPartitionSize, bool (*makeComparison)(int, int)) {
    quickSortRecursiveOrder(0, size - 1, itens, quickSortMaxPartitionSize, size, makeComparison);
}
