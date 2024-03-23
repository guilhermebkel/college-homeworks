#include <iostream>
#include "quick-sort-utils.h"

void quickSortNonRecursive(int itens[MAX_ARRAY_SIZE], int size, int quickSortMaxPartitionSize, bool (*makeComparison)(int, int)) {
    int stack[size];
    int top = -1;
    int left, right;

    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        right = stack[top--];
        left = stack[top--];

        int currentPartitionSize = right - left;
        bool isCurrentPartitionSizeOverMaxValue = currentPartitionSize > quickSortMaxPartitionSize;

        if (isCurrentPartitionSizeOverMaxValue) {
            insertionSort(left, right + 1, itens, makeComparison);
        } else {
            int i = left;
            int j = right;

            quickSortPartition(left, right, &i, &j, itens, -1, size, makeComparison);

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
