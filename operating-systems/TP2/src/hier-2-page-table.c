#include <stdio.h>
#include <stdlib.h>

#define HIER_2_LEVEL_ENTRIES (1 << 11)

int** hier2PageTable;

void initHier2PageTable() {
	hier2PageTable = malloc(sizeof(int*) * HIER_2_LEVEL_ENTRIES);

	for (unsigned i = 0; i < HIER_2_LEVEL_ENTRIES; i++) {
		hier2PageTable[i] = NULL;
	}
}

int getHier2FrameIndex(unsigned page) {
	unsigned first = page >> 11;
	unsigned second = page & (HIER_2_LEVEL_ENTRIES - 1);
	if (!hier2PageTable[first]) return -1;
	return hier2PageTable[first][second];
}

void setHier2FrameIndex(unsigned page, int frameIndex) {
	unsigned first = page >> 11;
	unsigned second = page & (HIER_2_LEVEL_ENTRIES - 1);
	if (!hier2PageTable[first]) {
			hier2PageTable[first] = malloc(sizeof(int) * HIER_2_LEVEL_ENTRIES);
			for (int i = 0; i < HIER_2_LEVEL_ENTRIES; i++) hier2PageTable[first][i] = -1;
	}
	hier2PageTable[first][second] = frameIndex;
}

void removeHier2FrameIndex(unsigned page) {
	setHier2FrameIndex(page, -1);
}

void clearHier2PageTable() {
	for (int i = 0; i < HIER_2_LEVEL_ENTRIES; i++) {
		if (hier2PageTable[i]) free(hier2PageTable[i]);
	}
	
	free(hier2PageTable);
}
