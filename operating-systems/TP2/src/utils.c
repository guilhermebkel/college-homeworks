#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

ReplacementAlgorithm turnStringIntoReplacementAlgorithm(const char* str) {
	if (strcmp(str, "lru") == 0) return LRU;
	else if (strcmp(str, "fifo") == 0) return FIFO;
	else if (strcmp(str, "optimal") == 0) return OPTIMAL;
	else if (strcmp(str, "random") == 0) return RANDOM;
	else if (strcmp(str, "lfu") == 0) return LFU;
	else return -1;
}

PageTableType turnStringIntoPageTableType(const char* str) {
	if (strcmp(str, "densa") == 0) return DENSE;
	else if (strcmp(str, "hier2") == 0) return HIER2;
	else if (strcmp(str, "hier3") == 0) return HIER3;
	else if (strcmp(str, "invertida") == 0) return INVERTED;
	else return -1;
}

const char* getReplacementAlgorithmName(ReplacementAlgorithm replacementAlgorithm) {
	switch (replacementAlgorithm) {
		case LRU: return "lru";
		case FIFO: return "fifo";
		case RANDOM: return "random";
		case LFU: return "lfu";
		case OPTIMAL: return "optimal (não implementado)";
		default: return "desconhecido";
	}
}

const char* getPageTableTypeName(PageTableType type) {
	switch (type) {
		case DENSE: return "densa";
		case HIER2: return "hier2";
		case HIER3: return "hier3";
		case INVERTED: return "invertida";
		default: return "desconhecido";
	}
}

unsigned calculatePageShiftBits(unsigned pageSizeInKB) {
	unsigned s = 0, tmp = pageSizeInKB;
	while (tmp > 1) { tmp >>= 1; s++; }
	return s;
}
