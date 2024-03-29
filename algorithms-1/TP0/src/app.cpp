#include <iostream>
#include "quick-sort-recursive.h"
#include "quick-sort-iterative.h"

int main () {
	int size = 8;
	int maxPartitionSize = 4;
	int items[size] = {5, 1, 4, 8, 7, 2, 3, 6};

	quickSortRecursive(items, size, maxPartitionSize, [](int a, int b) -> bool { return a > b; });
	// quickSortIterative(items, size, maxPartitionSize, [](int a, int b) -> bool { return a > b; });

	std::cout << "Array ordenado: ";
    for (int i = 0; i < size; ++i) {
        std::cout << items[i] << " ";
    }
    std::cout << std::endl;

	return 0;
}
