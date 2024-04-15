#include <iostream>
#include <vector>
#include "quick-sort-recursive.hpp"
#include "quick-sort-iterative.hpp"

int main() {
    std::vector<int> items = {5, 1, 4, 8, 7, 2, 3, 6};

    QuicksortRecursivoPuro(items);
    QuicksortRecursivoOrdenacaoInsercao(items);
    QuicksortNaoRecursivoPuro(items);
    QuicksortNaoRecursivoOrdenacaoInsercao(items);

    std::cout << "Array ordenado: ";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << items[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
