#ifndef PAGE_REPLACEMENT_ALGORITHM_HEADER
#define PAGE_REPLACEMENT_ALGORITHM_HEADER

typedef struct {
	int pageNumber;
	unsigned lastAccessTime;
	unsigned accessCount;
	int dirty;
	unsigned loadTime;
} Frame;

int getEvictedFrameIndexByRandom(Frame* memory, unsigned numFrames);
int getEvictedFrameIndexByFIFO(Frame* memory, unsigned numFrames);
int getEvictedFrameIndexByLRU(Frame* memory, unsigned numFrames);
int getEvictedFrameIndexByLFU(Frame* memory, unsigned numFrames);

#endif
