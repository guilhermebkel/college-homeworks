#ifndef UTILS_HEADER
#define UTILS_HEADER

typedef enum {
	LRU,
	FIFO,
	OPTIMAL,
	RANDOM,
	LFU
} ReplacementAlgorithm;

typedef enum {
	DENSE,
	HIER2,
	HIER3,
	INVERTED
} PageTableType;

ReplacementAlgorithm turnStringIntoReplacementAlgorithm(const char* str);
PageTableType turnStringIntoPageTableType(const char* str);
const char* getReplacementAlgorithmName(ReplacementAlgorithm replacementAlgorithm);
const char* getPageTableTypeName(PageTableType type);
unsigned calculatePageShiftBits(unsigned pageSizeInKB);

#endif
