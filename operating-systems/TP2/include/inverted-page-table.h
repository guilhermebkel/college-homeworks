#ifndef INVERTED_PAGE_TABLE_HEADER
#define INVERTED_PAGE_TABLE_HEADER

void initInvertedPageTable();
int getInvertedFrameIndex(unsigned page);
void setInvertedFrameIndex(unsigned page, int frameIndex);
void removeInvertedFrameIndex(unsigned page);
void clearInvertedPageTable();

#endif
