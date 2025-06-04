#ifndef PAGE_REPLACEMENT_ALGORITHM_HEADER
#define PAGE_REPLACEMENT_ALGORITHM_HEADER

typedef struct {
	int pageNumber;
	unsigned lastAccessTime;
	unsigned accessCount;
	int dirty;
	unsigned loadTime;
} Frame;

int getEvictedPageIndexByRandom(Frame* memory, unsigned numFrames);
int getEvictedPageIndexByFIFO(Frame* memory, unsigned numFrames);
int getEvictedPageIndexByLRU(Frame* memory, unsigned numFrames);
int getEvictedPageIndexByLFU(Frame* memory, unsigned numFrames);

#endif
