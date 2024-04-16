#include <iostream>
#include <vector>
#include <chrono>

double calculateFibonacciDuration (int (*fibonacciFunction)(int), int n) {
    auto start = std::chrono::steady_clock::now();
    fibonacciFunction(n);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end - start;

    return duration.count();
}
