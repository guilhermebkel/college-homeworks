#include <stdio.h>
#include <stdlib.h>

#define DENSE_PAGE_TABLE_SIZE (1 << 21)

int* densePageTable;

void initDensePageTable () {
	densePageTable = malloc(sizeof(int) * DENSE_PAGE_TABLE_SIZE);

	for (unsigned pageIndex = 0; pageIndex < DENSE_PAGE_TABLE_SIZE; pageIndex++) {
		densePageTable[pageIndex] = -1;
	}
}

int getDensePageTableFrameIndex(unsigned page) {
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