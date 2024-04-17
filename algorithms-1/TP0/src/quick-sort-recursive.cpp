#include <iostream>
#include <vector>
#include "quick-sort-utils.hpp"

void quickSortRecursive(int left, int right, std::vector<int> &items, int insertionSortPartitionSize, bool (*makeComparison)(int, int)) {
    if (mustUseInsertionSortAlgorithm(left, right, insertionSortPartitionSize)) {
        insertionSort(left, right + 1, items, makeComparison);
    } else {
        int i, j;

        quickSortPartition(left, right, &i, &j, items, makeComparison);

        if (left < j) {
            quickSortRecursive(left, j, items, insertionSortPartitionSize, makeComparison);
        }

        if (i < right) {
            quickSortRecursive(i, right, items, insertionSortPartitionSize, makeComparison);
        }
    }
}

std::vector<int> QuicksortRecursivoPuro(const std::vector<int> arr) {
    std::vector<int> items = arr;

    quickSortRecursive(0, items.size() - 1, items, DISABLED_INSERTION_SORT_PARTITION_SIZE, makeDefaultSortingComparison);

    return items;
}

std::vector<int> QuicksortRecursivoOrdenacaoInsercao(const std::vector<int> arr) {
    std::vector<int> items = arr;

    quickSortRecursive(0, items.size() - 1, items, DEFAULT_INSERTION_SORT_PARTITION_SIZE, makeDefaultSortingComparison);

    return items;
}
