#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

ReplacementAlgorithm turnStringIntoReplacementAlgorithm(const char* str) {
	if (strcmp(str, "lru") == 0) {
		return LRU;
	} else if (strcmp(str, "fifo") == 0) {
		return FIFO;
	} else if (strcmp(str, "random") == 0) {
		return RANDOM;
	} else if (strcmp(str, "lfu") == 0) {
		return LFU;
	} else {
		return -1;
	}
}

PageTableType turnStringIntoPageTableType(const char* str) {
	if (strcmp(str, "densa") == 0) {
		return DENSE;
	} else if (strcmp(str, "hier2") == 0) {
		return HIER2;
	} else if (strcmp(str, "hier3") == 0) {
		return HIER3;
	} else if (strcmp(str, "invertida") == 0) {
		return INVERTED;
	} else {
		return -1;
	}
}

const char* getReplacementAlgorithmName(ReplacementAlgorithm replacementAlgorithm) {
	if (replacementAlgorithm == LRU) {
		return "lru";
	} else if (replacementAlgorithm == FIFO) {
		return "fifo";
	} else if (replacementAlgorithm == RANDOM) {
		return "random";
	} else if (replacementAlgorithm == LFU) {
		return "lfu";
	} else {
		return "desconhecido";
	}
}

const char* getPageTableTypeName(PageTableType type) {
	if (type == DENSE) {
		return "densa";
	} else if (type == HIER2) {
		return "hier2";
	} else if (type == HIER3) {
		return "hier3";
	} else if (type == INVERTED) {
		return "invertida";
	} else {
		return "desconhecido";
	}
}

unsigned calculatePageShiftBits(unsigned pageSizeInKB) {
	unsigned shiftBits = 0;
	unsigned pageSize = pageSizeInKB;

	while (pageSize > 1) {
		pageSize >>= 1;
		shiftBits++;
	}

	return shiftBits;
}
