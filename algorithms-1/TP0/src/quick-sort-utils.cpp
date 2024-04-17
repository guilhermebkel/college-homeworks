#include <iostream>
#include <vector>
#include "quick-sort-utils.hpp"

bool mustUseInsertionSortAlgorithm (int left, int right, int insertionSortPartitionSize) {
    int currentPartitionSize = right - left;
    bool isInsertionSortPartitionSizeEnabled = insertionSortPartitionSize != DISABLED_INSERTION_SORT_PARTITION_SIZE;
    bool isCurrentPartitionSizeBelowInsertionSortPartitionSize = currentPartitionSize <= insertionSortPartitionSize;
    bool mustUseInsertionSortAlgorithm = isInsertionSortPartitionSizeEnabled && isCurrentPartitionSizeBelowInsertionSortPartitionSize;

    return mustUseInsertionSortAlgorithm;
}

void insertionSort (int left, int right, std::vector<int> &items, bool (*makeComparison)(int, int)) {
    for (int i = left + 1; i < right; i++) {
        int value = items[i];
        int j = i - 1;

        while (j >= left && makeComparison(items[j], value)) {
            items[j + 1] = items[j];
            j--;
        }

        items[j + 1] = value;
    }
}

void quickSortPartition (int left, int right, int *i, int *j, std::vector<int> &items, bool (*makeComparison)(int, int)) {
    int x, w;

    *i = left;
    *j = right;

    x = items[(*i + *j) / 2];

    do {
        while (makeComparison(x, items[*i])) {
            (*i)++;
        }

        while (makeComparison(items[*j], x)) {
            (*j)--;
        }

        if (*i <= *j) {
            w = items[*i];
            items[*i] = items[*j];
            items[*j] = w;

            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

bool makeDefaultSortingComparison (int a, int b) {
    return a > b;
}
