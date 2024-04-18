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
    int testItemsCount = 10000;

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
    int currentFibonacciRecursiveTestSize = 0;
    double fibonacciRecursiveTestDurationInSeconds = 0;
    std::vector<FibonacciTest> fibonacciRecursiveTests = generateFibonacciTests();
    size_t currentFibonacciRecursiveTestIndex = 0;

    int currentFibonacciNonRecursiveTestSize = 0;
    double fibonacciNonRecursiveTestDurationInSeconds = 0;
    std::vector<FibonacciTest> fibonacciNonRecursiveTests = generateFibonacciTests();
    size_t currentFibonacciNonRecursiveTestIndex = 0;

    while (true) {
        bool fibonacciRecursiveTestFinished = currentFibonacciRecursiveTestIndex >= fibonacciRecursiveTests.size();

        if (!fibonacciRecursiveTestFinished) {
            FibonacciTest currentFibonacciRecursiveTest = fibonacciRecursiveTests.at(currentFibonacciRecursiveTestIndex);

            if (fibonacciRecursiveTestDurationInSeconds > currentFibonacciRecursiveTest.seconds) {
                currentFibonacciRecursiveTest.value = currentFibonacciRecursiveTestSize - 1;
                fibonacciRecursiveTests[currentFibonacciRecursiveTestIndex] = currentFibonacciRecursiveTest;

                currentFibonacciRecursiveTestIndex++;
            } else {
                fibonacciRecursiveTestDurationInSeconds = calculateFibonacciDuration(fibonacciRecursive, currentFibonacciRecursiveTestSize);
                currentFibonacciRecursiveTestSize++;
            }
        }

        bool fibonacciNonRecursiveTestFinished = currentFibonacciNonRecursiveTestIndex >= fibonacciNonRecursiveTests.size();

        if (!fibonacciNonRecursiveTestFinished) {
            FibonacciTest currentFibonacciNonRecursiveTest = fibonacciNonRecursiveTests.at(currentFibonacciNonRecursiveTestIndex);

            if (fibonacciNonRecursiveTestDurationInSeconds > currentFibonacciNonRecursiveTest.seconds) {
                currentFibonacciNonRecursiveTest.value = currentFibonacciNonRecursiveTestSize - 1;
                fibonacciNonRecursiveTests[currentFibonacciNonRecursiveTestIndex] = currentFibonacciNonRecursiveTest;

                currentFibonacciNonRecursiveTestIndex++;
            } else {
                fibonacciNonRecursiveTestDurationInSeconds = calculateFibonacciDuration(fibonacciNonRecursive, currentFibonacciNonRecursiveTestSize);
                currentFibonacciNonRecursiveTestSize = (currentFibonacciNonRecursiveTestSize + 1) * 100;
            }
        }

        if (fibonacciRecursiveTestFinished && fibonacciNonRecursiveTestFinished) {
            break;
        }
    }

    std::cout << "Fibonacci Recursivo: ";
    for (const auto& test : fibonacciRecursiveTests) {
        std::cout << test.seconds << "s" << " -> n = " << test.value << "; ";
    }
    std::cout << std::endl;

    std::cout << "Fibonacci Não Recursivo: ";
    for (const auto& test : fibonacciNonRecursiveTests) {
        std::cout << test.seconds << "s" << " -> n = " << test.value << "; ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << std::endl;
    // testQuicksortAlgorithms();
    std::cout << std::endl;
    testFibonacciAlgorithms();
    std::cout << std::endl;

    return 0;
}
