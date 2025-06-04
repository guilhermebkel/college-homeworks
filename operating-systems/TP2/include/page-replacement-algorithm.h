#ifndef PAGE_REPLACEMENT_ALGORITHM_HEADER
#define PAGE_REPLACEMENT_ALGORITHM_HEADER

#include "utils.h"

int getEvictedFrameIndexByRandom(Frame* memory, unsigned numFrames);
int getEvictedFrameIndexByFIFO(Frame* memory, unsigned numFrames);
int getEvictedFrameIndexByLRU(Frame* memory, unsigned numFrames);
int getEvictedFrameIndexByLFU(Frame* memory, unsigned numFrames);

#endif
