#include <stdio.h>
#include <stdlib.h>

#define DENSE_PAGE_TABLE_SIZE (1 << 21)

int* densePageTable;

void initDensePageTable () {
	densePageTable = malloc(sizeof(int) * DENSE_PAGE_TABLE_SIZE);

	for (unsigned i = 0; i < DENSE_PAGE_TABLE_SIZE; i++) {
		densePageTable[i] = -1;
	}
}

int getDenseFrameIndex(unsigned page) {
	return densePageTable[page];
}

void setDenseFrameIndex(unsigned page, int frameIndex) {
	densePageTable[page] = frameIndex;
}

void removeDenseFrameIndex(unsigned page) {
	setDenseFrameIndex(page, -1);
}

void clearDensePageTable() {
	free(densePageTable);
}