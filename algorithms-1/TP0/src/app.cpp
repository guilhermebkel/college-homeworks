#include <iostream>
#include <vector>
#include "quick-sort-test.hpp"
#include "quick-sort-non-recursive.hpp"
#include "quick-sort-recursive.hpp"
#include "fibonacci-test.hpp"
#include "fibonacci-non-recursive.hpp"
#include "fibonacci-recursive.hpp"

void testQuicksortAlgorithms () {
    int testSetSize = 50;
    int testItemsCount = 100;

    std::vector<double> quicksortRecursivePureDurations;
    std::vector<double> quicksortRecursiveInsertionSortDurations;
    std::vector<double> quicksortNonRecursivePureDurations;
    std::vector<double> quicksortNonRecursiveInsertionSortDurations;

    for (int i = 0; i < testSetSize; ++i) {
        std::vector<int> items = generateRandomItems(testItemsCount);

        quicksortRecursivePureDurations.push_back(calculateQuicksortDuration(QuicksortRecursivoPuro, items));
        quicksortRecursiveInsertionSortDurations.push_back(calculateQuicksortDuration(QuicksortRecursivoOrdenacaoInsercao, items));
        quicksortNonRecursivePureDurations.push_back(calculateQuicksortDuration(QuicksortNaoRecursivoPuro, items));
        quicksortNonRecursiveInsertionSortDurations.push_back(calculateQuicksortDuration(QuicksortNaoRecursivoOrdenacaoInsercao, items));
    }

    double average, standardDeviation;

    calculateAverageAndStandardDeviation(quicksortRecursivePureDurations, average, standardDeviation);
    std::cout << "Quicksort Recursivo [Puro]: Média = " << average << ", Desvio Padrão = " << standardDeviation << std::endl;

    calculateAverageAndStandardDeviation(quicksortRecursiveInsertionSortDurations, average, standardDeviation);
    std::cout << "Quicksort Recursivo [Ordenação Inserção]: Média = " << average << ", Desvio Padrão = " << standardDeviation << std::endl;

    calculateAverageAndStandardDeviation(quicksortNonRecursivePureDurations, average, standardDeviation);
    std::cout << "Quicksort Não Recursivo [Puro]: Média = " << average << ", Desvio Padrão = " << standardDeviation << std::endl;

    calculateAverageAndStandardDeviation(quicksortNonRecursiveInsertionSortDurations, average, standardDeviation);
    std::cout << "Quicksort Não Recursivo [Ordenação Inserção]: Média = " << average << ", Desvio Padrão = " << standardDeviation << std::endl;
}

void testFibonacciAlgorithms () {
    int testSize = 44;

    double fibonacciRecursiveDuration = calculateFibonacciDuration(fibonacciRecursive, testSize);
    std::cout << "Fibonacci Recursivo: Duração = " << fibonacciRecursiveDuration << std::endl;

    double fibonacciNonRecursiveDuration = calculateFibonacciDuration(fibonacciNonRecursive, testSize);
    std::cout << "Fibonacci Não Recursivo: Duração = " << fibonacciNonRecursiveDuration << std::endl;
}

int main() {
    std::cout << std::endl;
    testQuicksortAlgorithms();
    std::cout << std::endl;
    testFibonacciAlgorithms();
    std::cout << std::endl;

    return 0;
}
