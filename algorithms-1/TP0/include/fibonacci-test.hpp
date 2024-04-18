#ifndef FIBONACCI_TEST_H
#define FIBONACCI_TEST_H

typedef struct {
    int seconds;
    int value;
} FibonacciTest;

double calculateFibonacciDuration (int (*fibonacciFunction)(int), int n);
std::vector<FibonacciTest> generateFibonacciTests ();

#endif
