#include <iostream>
#include "quick-sort-utils.hpp"

bool mustUseInsertionSortAlgorithm (int left, int right, int quickSortMaxPartitionSize) {
    int currentPartitionSize = right - left;
    bool maxPartitionSizeExists = quickSortMaxPartitionSize != -1;
    bool isCurrentPartitionSizeOverMaxValue = currentPartitionSize > quickSortMaxPartitionSize;
    bool mustUseInsertionSortAlgorithm = maxPartitionSizeExists && isCurrentPartitionSizeOverMaxValue;

    return mustUseInsertionSortAlgorithm;
}

void insertionSort (int left, int right, int itens[MAX_ARRAY_SIZE], bool (*makeComparison)(int, int)) {
    for (int i = left + 1; i < right; i++) {
        int value = itens[i];
        int j = i - 1;

        while (j >= left && makeComparison(itens[j], value)) {
            itens[j + 1] = itens[j];
            j--;
        }

        itens[j + 1] = value;
    }
}

void quickSortPartition (int left, int right, int *i, int *j, int itens[MAX_ARRAY_SIZE], bool (*makeComparison)(int, int)) {
    int x, w;

    *i = left;
    *j = right;

    x = itens[(*i + *j) / 2];

    do {
        while (makeComparison(x, itens[*i])) {
            (*i)++;
        }

        while (makeComparison(itens[*j], x)) {
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
