#include <stdio.h>
#include <stdlib.h>

#define HIER_3_LEVEL_ENTRIES (1 << 11)

int*** hier3PageTable;

void initHier3PageTable() {
	hier3PageTable = malloc(sizeof(int**) * HIER_3_LEVEL_ENTRIES);

	for (int firstLevelIndex = 0; firstLevelIndex < HIER_3_LEVEL_ENTRIES; firstLevelIndex++) {
		hier3PageTable[firstLevelIndex] = NULL;
	}
}

int getHier3PageTableFrameIndex(unsigned page) {
	unsigned firstLevelIndex = page >> 22;
	unsigned secondLevelIndex = (page >> 11) & (HIER_3_LEVEL_ENTRIES - 1);
	unsigned thirdLevelIndex = page & (HIER_3_LEVEL_ENTRIES - 1);
	
	int isPageTableLevelInvalid = !hier3PageTable[firstLevelIndex] || !hier3PageTable[firstLevelIndex][secondLevelIndex];

	if (isPageTableLevelInvalid) {
		return -1;
	}
	
	return hier3PageTable[firstLevelIndex][secondLevelIndex][thirdLevelIndex];
}

void setHier3PageTableFrameIndex(unsigned page, int frameIndex) {
	unsigned firstLevelIndex = page >> 22;
	unsigned secondLevelIndex = (page >> 11) & (HIER_3_LEVEL_ENTRIES - 1);
	unsigned thirdLevelIndex = page & (HIER_3_LEVEL_ENTRIES - 1);

	int isFirstLevelEmpty = !hier3PageTable[firstLevelIndex];

	if (isFirstLevelEmpty) {
		hier3PageTable[firstLevelIndex] = malloc(sizeof(int*) * HIER_3_LEVEL_ENTRIES);

		for (int secondLevel = 0; secondLevel < HIER_3_LEVEL_ENTRIES; secondLevel++) {
			hier3PageTable[firstLevelIndex][secondLevel] = NULL;
		}
	}

	int isSecondLevelEmpty = !hier3PageTable[firstLevelIndex][secondLevelIndex];

	if (isSecondLevelEmpty) {
		hier3PageTable[firstLevelIndex][secondLevelIndex] = malloc(sizeof(int) * HIER_3_LEVEL_ENTRIES);

		for (int thirdLevel = 0; thirdLevel < HIER_3_LEVEL_ENTRIES; thirdLevel++) {
			hier3PageTable[firstLevelIndex][secondLevelIndex][thirdLevel] = -1;
		}
	}

	hier3PageTable[firstLevelIndex][secondLevelIndex][thirdLevelIndex] = frameIndex;
}

void removeHier3PageTableFrameIndex(unsigned page) {
	setHier3PageTableFrameIndex(page, -1);
}

void clearHier3PageTable() {
	for (int firstLevelIndex = 0; firstLevelIndex < HIER_3_LEVEL_ENTRIES; firstLevelIndex++) {
		if (hier3PageTable[firstLevelIndex]) {
			for (int secondLevelIndex = 0; secondLevelIndex < HIER_3_LEVEL_ENTRIES; secondLevelIndex++) {
				if (hier3PageTable[firstLevelIndex][secondLevelIndex]) {
					free(hier3PageTable[firstLevelIndex][secondLevelIndex]);
				}
			}

			free(hier3PageTable[firstLevelIndex]);
		}
	}

	free(hier3PageTable);
}
