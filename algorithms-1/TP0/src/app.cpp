#include <iostream>
#include "quick-sort-recursive.h"
#include "quick-sort-non-recursive.h"

using ComparisonFunction = bool (*)(int, int);

int main () {
	int size = 8;
	int maxPartitionSize = 50;
	int items[size] = {5, 1, 4, 8, 7, 2, 3, 6};

	ComparisonFunction comparisonFunction = [](int a, int b) { return a > b; };
	// quickSortRecursive(items, 8, maxPartitionSize, comparisonFunction);
	quickSortNonRecursive(items, 8, maxPartitionSize, comparisonFunction);

	std::cout << "Array ordenado: ";
    for (int i = 0; i < size; ++i) {
        std::cout << items[i] << " ";
    }
    std::cout << std::endl;

	return 0;
}
