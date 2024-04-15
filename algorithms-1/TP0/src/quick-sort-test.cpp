#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <numeric>
#include <cmath>

std::vector<int> generateRandomItems (int size) {
    std::vector<int> items;
    items.reserve(size);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    for (int i = 0; i < size; ++i) {
        items.push_back(dis(gen));
    }

    return items;
}

double calculateSortingDuration (std::vector<int> (*sortingFunction)(std::vector<int>), const std::vector<int> &items) {
    auto start = std::chrono::steady_clock::now();
    sortingFunction(items);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end - start;

    return duration.count();
}

void calculateAverageAndStandardDeviation(const std::vector<double>& durations, double& average, double& standardDeviation) {
    average = std::accumulate(durations.begin(), durations.end(), 0.0) / durations.size();

    double acumulado = 0.0;

    for (double tempo : durations) {
        acumulado += (tempo - average) * (tempo - average);
    }

    standardDeviation = std::sqrt(acumulado / durations.size());
}
