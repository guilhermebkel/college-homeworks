#ifndef HIER_3_PAGE_TABLE_HEADER
#define HIER_3_PAGE_TABLE_HEADER

void initHier3PageTable();
int getHier3FrameIndex(unsigned page);
void setHier3FrameIndex(unsigned page, int frameIndex);
void removeHier3FrameIndex(unsigned page);
void clearHier3PageTable();

#endif
