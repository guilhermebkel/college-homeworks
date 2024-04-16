#ifndef QUICK_SORT_TEST_H
#define QUICK_SORT_TEST_H

std::vector<int> generateRandomItems (int size);
double calculateQuicksortDuration (std::vector<int> (*quicksortFunction)(std::vector<int>), const std::vector<int> &items);
void calculateAverageAndStandardDeviation(const std::vector<double>& durations, double& average, double& standardDeviation);

#endif