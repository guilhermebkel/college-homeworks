#include <iostream>
#include "quick-sort-utils.h"

void insertionSort(int left, int right, int itens[MAX_ARRAY_SIZE], bool (*makeComparison)(int, int)) {
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

void quickSortPartition(int left, int right, int *i, int *j, int itens[MAX_ARRAY_SIZE], int quickSortPivot, int size, bool (*makeComparison)(int, int)) {
    int x, w;

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
