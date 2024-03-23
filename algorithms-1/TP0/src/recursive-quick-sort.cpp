#include <iostream>

#include "recursive-quick-sort.h"

template <typename Model>
void quickSortPartition(int left, int right, int *i, int *j, Item<Model> itens[MAX_ARRAY_SIZE], int quickSortPivot, int size, bool (*makeComparison)(Model, Model)) {
    Item<Model> x, w;

    *i = left;
    *j = right;

    bool isFirstPartition = left == 0 && right == size - 1;
    bool customPivotExists = quickSortPivot != -1;
    bool customPivotIsBetweenPartition = quickSortPivot >= left && quickSortPivot <= right;
    bool canUseCustomPivot = isFirstPartition && customPivotExists && customPivotIsBetweenPartition;

    if (canUseCustomPivot) {
        x = itens[quickSortPivot];
    } else {
        x = itens[(*i + *j) / 2];
    }

    do {
        while (makeComparison(x.model, itens[*i].model)) {
            (*i)++;
        }

        while (makeComparison(itens[*j].model, x.model)) {
            (*j)--;
        }

        if (*i <= *j) {
            w = itens[*i];
            itens[*i] = itens[*j];
            itens[*j] = w;

            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

template <typename Model>
void recursiveQuickSortOrder(int left, int right, Item<Model> itens[MAX_ARRAY_SIZE], int quickSortMaxPartitionSize, int size, bool (*makeComparison)(Model, Model)) {
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
void insertionSort(int left, int right, Item<Model> itens[MAX_ARRAY_SIZE], bool (*makeComparison)(Model, Model)) {
    for (int i = left + 1; i < right; i++) {
        Item<Model> key = itens[i];
        int j = i - 1;

        while (j >= left && makeComparison(key.model, itens[j].model)) {
            itens[j + 1] = itens[j];
            j--;
        }

        itens[j + 1] = key;
    }
}
