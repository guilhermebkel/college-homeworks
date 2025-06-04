#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "page-replacement-algorithm.h"

int getPageToEvictByRandom(Frame* memory, unsigned numFrames) {
	return rand() % numFrames;
}

int getPageToEvictByFIFO(Frame* memory, unsigned numFrames) {
	int minLoadTime = INT_MAX, index = 0;
	for (unsigned i = 0; i < numFrames; i++) {
		if (memory[i].loadTime < minLoadTime) {
			minLoadTime = memory[i].loadTime;
			index = i;
		}
	}
	return index;
}

int getPageToEvictByLRU(Frame* memory, unsigned numFrames) {
	int oldestTime = INT_MAX, index = 0;
	for (unsigned i = 0; i < numFrames; i++) {
		if (memory[i].lastAccessTime < oldestTime) {
			oldestTime = memory[i].lastAccessTime;
			index = i;
		}
	}
	return index;
}

int getPageToEvictByLFU(Frame* memory, unsigned numFrames) {
	int leastAccessed = INT_MAX, index = 0;
	for (unsigned i = 0; i < numFrames; i++) {
		if (memory[i].accessCount < leastAccessed) {
			leastAccessed = memory[i].accessCount;
			index = i;
		}
	}
	return index;
}