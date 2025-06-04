#include <stdio.h>
#include <stdlib.h>

#define INVERTED_TABLE_SIZE 4096

int* densePageTable;
int** hier2PageTable;
int*** hier3PageTable;

typedef struct InvertedPageEntry {
	unsigned pageNumber;
	int frameIndex;
	struct InvertedPageEntry* next;
} InvertedPageEntry;

InvertedPageEntry** invertedPageTable;

unsigned hashPageNumber(unsigned page) {
	return page % INVERTED_TABLE_SIZE;
}

void initInvertedPageTable() {
	invertedPageTable = calloc(INVERTED_TABLE_SIZE, sizeof(InvertedPageEntry*));
}

int getInvertedPageTableFrameIndex(unsigned page) {
	unsigned pageNumberHash = hashPageNumber(page);
	InvertedPageEntry* currentEntry = invertedPageTable[pageNumberHash];

	while (currentEntry) {
		if (currentEntry->pageNumber == page) {
			return currentEntry->frameIndex;
		}

		currentEntry = currentEntry->next;
	}

	return -1;
}

void setInvertedPageTableFrameIndex(unsigned page, int frameIndex) {
	unsigned pageNumberHash = hashPageNumber(page);
	InvertedPageEntry* currentEntry = invertedPageTable[pageNumberHash];
	
	while (currentEntry) {
		if (currentEntry->pageNumber == page) {
			currentEntry->frameIndex = frameIndex;
			return;
		}

		currentEntry = currentEntry->next;
	}
	
	InvertedPageEntry* newEntry = malloc(sizeof(InvertedPageEntry));
	newEntry->pageNumber = page;
	newEntry->frameIndex = frameIndex;
	newEntry->next = invertedPageTable[pageNumberHash];
	invertedPageTable[pageNumberHash] = newEntry;
}

void removeInvertedPageTableFrameIndex(unsigned page) {
	unsigned pageNumberHash = hashPageNumber(page);
	InvertedPageEntry* currentEntry = invertedPageTable[pageNumberHash];
	InvertedPageEntry* previousEntry = NULL;

	while (currentEntry) {
		if (currentEntry->pageNumber == page) {
			if (previousEntry) {
				previousEntry->next = currentEntry->next;
			} else {
				invertedPageTable[pageNumberHash] = currentEntry->next;
			}

			free(currentEntry);
			return;
		}

		previousEntry = currentEntry;
		currentEntry = currentEntry->next;
	}
}

void clearInvertedPageTable() {
	for (int hashIndex = 0; hashIndex < INVERTED_TABLE_SIZE; hashIndex++) {
		InvertedPageEntry* currentEntry = invertedPageTable[hashIndex];

		while (currentEntry) {
			InvertedPageEntry* entryToFree = currentEntry;
			currentEntry = currentEntry->next;
			free(entryToFree);
		}
	}

	free(invertedPageTable);
}
