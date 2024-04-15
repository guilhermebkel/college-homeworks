#include <iostream>
#include <vector>
#include "quick-sort-recursive.hpp"
#include "quick-sort-iterative.hpp"
#include "fibonacci-recursive.hpp"
#include "fibonacci-iterative.hpp"

void testQuicksortAlgorithms () {
    std::vector<int> items = {5, 1, 4, 8, 7, 2, 3, 6};

    std::vector<int> sortedItems = QuicksortRecursivoPuro(items);
    // std::vector<int> sortedItems = QuicksortRecursivoOrdenacaoInsercao(items);
    // std::vector<int> sortedItems = QuicksortNaoRecursivoPuro(items);
    // std::vector<int> sortedItems = QuicksortNaoRecursivoOrdenacaoInsercao(items);

    std::cout << "Array ordenado: ";
    for (size_t i = 0; i < sortedItems.size(); ++i) {
        std::cout << sortedItems[i] << " ";
    }
    std::cout << std::endl;
}

void testFibonacciAlgorithms () {
    fibonacciIterative(10);
    fibonacciRecursive(10);
}

int main() {
    testQuicksortAlgorithms();
    testFibonacciAlgorithms();

    return 0;
}
