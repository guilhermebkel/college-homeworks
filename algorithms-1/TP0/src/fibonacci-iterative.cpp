#include <iostream>

int fibonacciIterative (int n) {
    int a = 0;
    int b = 1;
    int temp;

    if (n == 0) {
        return a;
    }
    
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }

    return b;
}
