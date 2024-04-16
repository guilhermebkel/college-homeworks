#ifndef QUICK_SORT_UTILS_H
#define QUICK_SORT_UTILS_H

#ifndef DEFAULT_INSERTION_SORT_PARTITION_SIZE 
#define DEFAULT_INSERTION_SORT_PARTITION_SIZE 30
#endif

#ifndef DISABLED_INSERTION_SORT_PARTITION_SIZE 
#define DISABLED_INSERTION_SORT_PARTITION_SIZE -1
#endif

void insertionSort(int left, int right, std::vector<int>&items, bool (*makeComparison)(int, int));
void quickSortPartition(int left, int right, int *i, int *j, std::vector<int> &items, bool (*makeComparison)(int, int));
bool mustUseInsertionSortAlgorithm (int left, int right, int quickSortMaxPartitionSize);
bool makeDefaultSortingComparison (int a, int b);

#endif