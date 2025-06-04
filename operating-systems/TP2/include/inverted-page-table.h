#ifndef INVERTED_PAGE_TABLE_HEADER
#define INVERTED_PAGE_TABLE_HEADER

void initInvertedPageTable();
int getInvertedPageTableFrameIndex(unsigned page);
void setInvertedPageTableFrameIndex(unsigned page, int frameIndex);
void removeInvertedPageTableFrameIndex(unsigned page);
void clearInvertedPageTable();

#endif
