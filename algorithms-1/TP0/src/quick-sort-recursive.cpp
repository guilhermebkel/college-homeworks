#include <iostream>
#include <vector>
#include "quick-sort-utils.hpp"

void quickSortRecursiveOrder(int left, int right, std::vector<int> &items, int quickSortMaxPartitionSize, bool (*makeComparison)(int, int)) {
    if (mustUseInsertionSortAlgorithm(left, right, quickSortMaxPartitionSize)) {
        insertionSort(left, right + 1, items, makeComparison);
    } else {
        int i, j;

        quickSortPartition(left, right, &i, &j, items, makeComparison);

        if (left < j) {
            quickSortRecursiveOrder(left, j, items, quickSortMaxPartitionSize, makeComparison);
        }

        if (i < right) {
            quickSortRecursiveOrder(i, right, items, quickSortMaxPartitionSize, makeComparison);
        }
    }
}

void quickSortRecursive(std::vector<int> &items, int quickSortMaxPartitionSize, bool (*makeComparison)(int, int)) {
    quickSortRecursiveOrder(0, items.size() - 1, items, quickSortMaxPartitionSize, makeComparison);
}

std::vector<int> QuicksortRecursivoPuro(const std::vector<int> arr) {
    std::vector<int> items = arr;

    quickSortRecursive(items, -1, makeDefaultSortingComparison);

    return items;
}

std::vector<int> QuicksortRecursivoOrdenacaoInsercao(const std::vector<int> arr) {
    std::vector<int> items = arr;

    quickSortRecursive(items, 50, makeDefaultSortingComparison);

    return items;
}
