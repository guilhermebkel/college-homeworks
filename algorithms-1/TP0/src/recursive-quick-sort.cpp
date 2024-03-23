#include <iostream>
#include "recursive-quick-sort.h"
#include "quick-sort-utils.h"

template <typename Model>
void recursiveQuickSortOrder(int left, int right, Model itens[MAX_ARRAY_SIZE], int quickSortMaxPartitionSize, int size, bool (*makeComparison)(Model, Model)) {
    int i, j;

    int currentPartitionSize = right - left;

    bool maxPartitionSizeExists = quickSortMaxPartitionSize != -1;
    bool isCurrentPartitionSizeOverMaxValue = currentPartitionSize > quickSortMaxPartitionSize;
    bool mustUseSimpleSortingAlgorithm = maxPartitionSizeExists && isCurrentPartitionSizeOverMaxValue;

    if (mustUseSimpleSortingAlgorithm) {
        insertionSort(left, right + 1, itens, makeComparison);
    } else {
        quickSortPartition(left, right, &i, &j, itens, -1, size, makeComparison);

        if (left < j) {
            recursiveQuickSortOrder(left, j, itens, quickSortMaxPartitionSize, size, makeComparison);
        }

        if (i < right) {
            recursiveQuickSortOrder(i, right, itens, quickSortMaxPartitionSize, size, makeComparison);
        }
    }
}

template <typename Model>
void recursiveQuickSort(Model itens[MAX_ARRAY_SIZE], int size, int quickSortMaxPartitionSize, bool (*makeComparison)(Model, Model)) {
    recursiveQuickSortOrder(0, size - 1, itens, quickSortMaxPartitionSize, size, makeComparison);
}

template <typename Model>
void insertionSort(int left, int right, Model itens[MAX_ARRAY_SIZE], bool (*makeComparison)(Model, Model)) {
    for (int i = left + 1; i < right; i++) {
        Model model = itens[i];
        int j = i - 1;

        while (j >= left && makeComparison(model, itens[j])) {
            itens[j + 1] = itens[j];
            j--;
        }

        itens[j + 1] = model;
    }
}
