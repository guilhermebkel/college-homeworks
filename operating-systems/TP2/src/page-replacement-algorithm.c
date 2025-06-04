#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "page-replacement-algorithm.h"

int getEvictedFrameIndexByRandom(Frame* memory, unsigned numFrames) {
	int evictedFrameIndex = rand() % numFrames;

	return evictedFrameIndex;
}

int getEvictedFrameIndexByFIFO(Frame* memory, unsigned numFrames) {
	int oldestLoadTime = INT_MAX;
	int evictedFrameIndex = 0;

	for (unsigned frameIndex = 0; frameIndex < numFrames; frameIndex++) {
		int isOlderLoadTime = memory[frameIndex].loadTime < oldestLoadTime;

		if (isOlderLoadTime) {
			oldestLoadTime = memory[frameIndex].loadTime;
			evictedFrameIndex = frameIndex;
		}
	}

	return evictedFrameIndex;
}

int getEvictedFrameIndexByLRU(Frame* memory, unsigned numFrames) {
	int oldestAccessTime = INT_MAX;
	int evictedFrameIndex = 0;

	for (unsigned frameIndex = 0; frameIndex < numFrames; frameIndex++) {
		int isOlderAccessTime = memory[frameIndex].lastAccessTime < oldestAccessTime;

		if (isOlderAccessTime) {
			oldestAccessTime = memory[frameIndex].lastAccessTime;
			evictedFrameIndex = frameIndex;
		}
	}

	return evictedFrameIndex;
}

int getEvictedFrameIndexByLFU(Frame* memory, unsigned numFrames) {
	int leastAccessCount = INT_MAX;
	int evictedFrameIndex = 0;

	for (unsigned frameIndex = 0; frameIndex < numFrames; frameIndex++) {
		int hasLessAccesses = memory[frameIndex].accessCount < leastAccessCount;

		if (hasLessAccesses) {
			leastAccessCount = memory[frameIndex].accessCount;
			evictedFrameIndex = frameIndex;
		}
	}

	return evictedFrameIndex;
}