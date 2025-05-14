#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LRU,
    FIFO,
    OPTIMAL
} ReplacementAlgorithm;

ReplacementAlgorithm turnStringIntoReplacementAlgorithm(const char* str) {
    if (strcmp(str, "lru") == 0) {
        return LRU;
    } else if (strcmp(str, "fifo") == 0) {
        return FIFO;
    } else if (strcmp(str, "optimal") == 0) {
        return OPTIMAL;
    } else {
        return -1;
    }
}

int main(int argc, char* argv[]) {
    ReplacementAlgorithm replacementAlgorithm = turnStringIntoReplacementAlgorithm(argv[1]);
    char* traceFilePath = argv[2];
    int pageSizeInKB = atoi(argv[3]);
    int memorySizeInKB = atoi(argv[4]);

    return 0;
}
