#include <iostream>
#include "quick-sort-utils.h"

template <typename Model>
void quickSortPartition(int left, int right, int *i, int *j, Model itens[MAX_ARRAY_SIZE], int quickSortPivot, int size, bool (*makeComparison)(Model, Model)) {
    Model x, w;

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
