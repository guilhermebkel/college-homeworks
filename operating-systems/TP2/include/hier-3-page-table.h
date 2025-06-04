#ifndef HIER_3_PAGE_TABLE_HEADER
#define HIER_3_PAGE_TABLE_HEADER

void initHier3PageTable();
int getHier3PageTableFrameIndex(unsigned page);
void setHier3PageTableFrameIndex(unsigned page, int frameIndex);
void removeHier3PageTableFrameIndex(unsigned page);
void clearHier3PageTable();

#endif
