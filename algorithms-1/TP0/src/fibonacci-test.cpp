#include <iostream>
#include <vector>
#include <chrono>
#include "fibonacci-test.hpp"

double calculateFibonacciDuration (int (*fibonacciFunction)(int), int n) {
    auto start = std::chrono::steady_clock::now();
    fibonacciFunction(n);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end - start;

    return duration.count();
}

std::vector<FibonacciTest> generateFibonacciTests () {
    std::vector<FibonacciTest> fibonacciTests = {
        { .seconds = 15, .value = 0 },
        { .seconds = 30, .value = 0 },
        { .seconds = 45, .value = 0 },
        { .seconds = 60, .value = 0 },
        { .seconds = 75, .value = 0 },
        { .seconds = 90, .value = 0 },
        { .seconds = 105, .value = 0 },
        { .seconds = 120, .value = 0 },
    };

    return fibonacciTests;
}
