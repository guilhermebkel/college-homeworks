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

int getInvertedFrameIndex(unsigned page) {
    unsigned hash = hashPageNumber(page);
    InvertedPageEntry* entry = invertedPageTable[hash];
    while (entry) {
        if (entry->pageNumber == page) return entry->frameIndex;
        entry = entry->next;
    }
    return -1;
}

void setInvertedFrameIndex(unsigned page, int frameIndex) {
    unsigned hash = hashPageNumber(page);
    InvertedPageEntry* entry = invertedPageTable[hash];
    while (entry) {
        if (entry->pageNumber == page) {
            entry->frameIndex = frameIndex;
            return;
        }
        entry = entry->next;
    }
    entry = malloc(sizeof(InvertedPageEntry));
    entry->pageNumber = page;
    entry->frameIndex = frameIndex;
    entry->next = invertedPageTable[hash];
    invertedPageTable[hash] = entry;
}

void removeInvertedFrameIndex(unsigned page) {
    unsigned hash = hashPageNumber(page);
    InvertedPageEntry* curr = invertedPageTable[hash];
    InvertedPageEntry* prev = NULL;
    while (curr) {
        if (curr->pageNumber == page) {
            if (prev) prev->next = curr->next;
            else invertedPageTable[hash] = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void clearInvertedPageTable() {
	for (int i = 0; i < INVERTED_TABLE_SIZE; i++) {
		InvertedPageEntry* entry = invertedPageTable[i];
		while (entry) {
			InvertedPageEntry* temp = entry;
			entry = entry->next;
			free(temp);
		}
	}

	free(invertedPageTable);
}
