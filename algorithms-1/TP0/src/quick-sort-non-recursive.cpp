#include <iostream>
#include <vector>
#include "quick-sort-utils.hpp"

void quickSortNonRecursive (std::vector<int> &items, int quickSortMaxPartitionSize, bool (*makeComparison)(int, int)) {
    int size = items.size();
    std::vector<int> stack(size);
    int top = -1;
    int left, right;

    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        right = stack[top--];
        left = stack[top--];

        if (mustUseInsertionSortAlgorithm(left, right, quickSortMaxPartitionSize)) {
            insertionSort(left, right + 1, items, makeComparison);
        } else {
            int i = left;
            int j = right;

            quickSortPartition(left, right, &i, &j, items, makeComparison);

            if (left < j) {
                stack[++top] = left;
                stack[++top] = j;
            }

            if (i < right) {
                stack[++top] = i;
                stack[++top] = right;
            }
        }
    }
}

std::vector<int> QuicksortNaoRecursivoPuro (const std::vector<int> arr) {
    std::vector<int> items = arr;

    quickSortNonRecursive(items, -1, makeDefaultSortingComparison);
    
    return items;
}

std::vector<int> QuicksortNaoRecursivoOrdenacaoInsercao(const std::vector<int> arr) {
    std::vector<int> items = arr;
    
    quickSortNonRecursive(items, INSERTION_SORT_PARTITION_SIZE, makeDefaultSortingComparison);
    
    return items;
}
