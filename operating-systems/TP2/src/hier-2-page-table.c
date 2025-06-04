#include <stdio.h>
#include <stdlib.h>

#define HIER_2_LEVEL_ENTRIES (1 << 11)

int** hier2PageTable;

void initHier2PageTable() {
	hier2PageTable = malloc(sizeof(int*) * HIER_2_LEVEL_ENTRIES);

	for (unsigned pageTableIndex = 0; pageTableIndex < HIER_2_LEVEL_ENTRIES; pageTableIndex++) {
		hier2PageTable[pageTableIndex] = NULL;
	}
}

int getHier2PageTableFrameIndex(unsigned page) {
	unsigned firstLevelIndex = page >> 11;
	unsigned secondLevelIndex = page & (HIER_2_LEVEL_ENTRIES - 1);

	if (!hier2PageTable[firstLevelIndex]) {
		return -1;
	}

	return hier2PageTable[firstLevelIndex][secondLevelIndex];
}

void setHier2PageTableFrameIndex(unsigned page, int frameIndex) {
	unsigned firstLevelIndex = page >> 11;
	unsigned secondLevelIndex = page & (HIER_2_LEVEL_ENTRIES - 1);

	if (!hier2PageTable[firstLevelIndex]) {
			hier2PageTable[firstLevelIndex] = malloc(sizeof(int) * HIER_2_LEVEL_ENTRIES);

			for (int secondTableIndex = 0; secondTableIndex < HIER_2_LEVEL_ENTRIES; secondTableIndex++) {
				hier2PageTable[firstLevelIndex][secondTableIndex] = -1;
			}
	}

	hier2PageTable[firstLevelIndex][secondLevelIndex] = frameIndex;
}

void removeHier2PageTableFrameIndex(unsigned page) {
	setHier2PageTableFrameIndex(page, -1);
}

void clearHier2PageTable() {
	for (int firstTableIndex = 0; firstTableIndex < HIER_2_LEVEL_ENTRIES; firstTableIndex++) {
		if (hier2PageTable[firstTableIndex]) {
			free(hier2PageTable[firstTableIndex]);
		}
	}
	
	free(hier2PageTable);
}
