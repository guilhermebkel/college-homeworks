#include <stdio.h>
#include <stdlib.h>

#define HIER_3_LEVEL_ENTRIES (1 << 11)

int*** hier3PageTable;

void initHier3PageTable() {
	hier3PageTable = malloc(sizeof(int**) * HIER_3_LEVEL_ENTRIES);

	for (int i = 0; i < HIER_3_LEVEL_ENTRIES; i++) {
		hier3PageTable[i] = NULL;
	}
}

int getHier3FrameIndex(unsigned page) {
	unsigned first = page >> 22;
	unsigned second = (page >> 11) & (HIER_3_LEVEL_ENTRIES - 1);
	unsigned third = page & (HIER_3_LEVEL_ENTRIES - 1);
	if (!hier3PageTable[first] || !hier3PageTable[first][second]) return -1;
	return hier3PageTable[first][second][third];
}

void setHier3FrameIndex(unsigned page, int frameIndex) {
	unsigned first = page >> 22;
	unsigned second = (page >> 11) & (HIER_3_LEVEL_ENTRIES - 1);
	unsigned third = page & (HIER_3_LEVEL_ENTRIES - 1);
	if (!hier3PageTable[first]) {
		hier3PageTable[first] = malloc(sizeof(int*) * HIER_3_LEVEL_ENTRIES);
		for (int i = 0; i < HIER_3_LEVEL_ENTRIES; i++) hier3PageTable[first][i] = NULL;
	}
	if (!hier3PageTable[first][second]) {
		hier3PageTable[first][second] = malloc(sizeof(int) * HIER_3_LEVEL_ENTRIES);
		for (int i = 0; i < HIER_3_LEVEL_ENTRIES; i++) hier3PageTable[first][i][i] = -1;
	}
	hier3PageTable[first][second][third] = frameIndex;
}

void removeHier3FrameIndex(unsigned page) {
	setHier3FrameIndex(page, -1);
}

void clearHier3PageTable() {
	for (int i = 0; i < HIER_3_LEVEL_ENTRIES; i++) {
		if (hier3PageTable[i]) {
			for (int j = 0; j < HIER_3_LEVEL_ENTRIES; j++) {
				if (hier3PageTable[i][j]) {
					free(hier3PageTable[i][j]);
				}
			}

			free(hier3PageTable[i]);
		}
	}

	free(hier3PageTable);
}
