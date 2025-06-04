#ifndef PAGE_REPLACEMENT_ALGORITHM_HEADER
#define PAGE_REPLACEMENT_ALGORITHM_HEADER

typedef struct {
	int pageNumber;
	unsigned lastAccessTime;
	unsigned accessCount;
	int dirty;
	unsigned loadTime;
} Frame;

int getPageToEvictByRandom(Frame* memory, unsigned numFrames);
int getPageToEvictByFIFO(Frame* memory, unsigned numFrames);
int getPageToEvictByLRU(Frame* memory, unsigned numFrames);
int getPageToEvictByLFU(Frame* memory, unsigned numFrames);

#endif
