#include <iostream>
#include <vector>
#include "quick-sort-non-recursive.hpp"
#include "quick-sort-recursive.hpp"
#include "quick-sort-test.hpp"
#include "fibonacci-non-recursive.hpp"
#include "fibonacci-recursive.hpp"

void testQuicksortAlgorithms () {
    int testSetSize = 50;

    std::vector<double> quicksortRecursivoPuroDurations;
    std::vector<double> quicksortRecursivoOrdenacaoInsercaoDurations;
    std::vector<double> quicksortNaoRecursivoPuroDurations;
    std::vector<double> quicksortNaoRecursivoOrdenacaoInsercaoDurations;

    for (int i = 0; i < testSetSize; ++i) {
        std::vector<int> items = generateRandomItems(100);

        quicksortRecursivoPuroDurations.push_back(calculateSortingDuration(QuicksortRecursivoPuro, items));
        quicksortRecursivoOrdenacaoInsercaoDurations.push_back(calculateSortingDuration(QuicksortRecursivoOrdenacaoInsercao, items));
        quicksortNaoRecursivoPuroDurations.push_back(calculateSortingDuration(QuicksortNaoRecursivoPuro, items));
        quicksortNaoRecursivoOrdenacaoInsercaoDurations.push_back(calculateSortingDuration(QuicksortNaoRecursivoOrdenacaoInsercao, items));
    }

    double average, standardDeviation;

    calculateAverageAndStandardDeviation(quicksortRecursivoPuroDurations, average, standardDeviation);
    std::cout << "QuicksortRecursivoPuro: Média = " << average << ", Desvio Padrão = " << standardDeviation << std::endl;

    calculateAverageAndStandardDeviation(quicksortRecursivoOrdenacaoInsercaoDurations, average, standardDeviation);
    std::cout << "QuicksortRecursivoOrdenacaoInsercao: Média = " << average << ", Desvio Padrão = " << standardDeviation << std::endl;

    calculateAverageAndStandardDeviation(quicksortNaoRecursivoPuroDurations, average, standardDeviation);
    std::cout << "QuicksortNaoRecursivoPuro: Média = " << average << ", Desvio Padrão = " << standardDeviation << std::endl;

    calculateAverageAndStandardDeviation(quicksortNaoRecursivoOrdenacaoInsercaoDurations, average, standardDeviation);
    std::cout << "QuicksortNaoRecursivoOrdenacaoInsercao: Média = " << average << ", Desvio Padrão = " << standardDeviation << std::endl;
}

void testFibonacciAlgorithms () {
    fibonacciNonRecursive(10);
    fibonacciRecursive(10);
}

int main() {
    testQuicksortAlgorithms();
    testFibonacciAlgorithms();

    return 0;
}
