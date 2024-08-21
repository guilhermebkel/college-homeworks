#include <iostream>
#include <vector>

#ifndef DEFAULT_INSERTION_SORT_PARTITION_SIZE 
#define DEFAULT_INSERTION_SORT_PARTITION_SIZE 30
#endif

#ifndef DISABLED_INSERTION_SORT_PARTITION_SIZE 
#define DISABLED_INSERTION_SORT_PARTITION_SIZE -1
#endif

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

void quickSortNonRecursive (std::vector<int> &items, int insertionSortPartitionSize, bool (*makeComparison)(int, int)) {
    int size = items.size();
    std::vector<int> stack(size);
    int top = -1;
    int left, right;

    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        right = stack[top--];
        left = stack[top--];

        if (mustUseInsertionSortAlgorithm(left, right, insertionSortPartitionSize)) {
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

std::vector<int> QuicksortNaoRecursivoPuro (const std::vector<int> arr) {
    std::vector<int> items = arr;

    quickSortNonRecursive(items, DISABLED_INSERTION_SORT_PARTITION_SIZE, makeDefaultSortingComparison);
    
    return items;
}

std::vector<int> QuicksortNaoRecursivoOrdenacaoInsercao(const std::vector<int> arr) {
    std::vector<int> items = arr;
    
    quickSortNonRecursive(items, DEFAULT_INSERTION_SORT_PARTITION_SIZE, makeDefaultSortingComparison);
    
    return items;
}

int main () {
    return 0;
}
