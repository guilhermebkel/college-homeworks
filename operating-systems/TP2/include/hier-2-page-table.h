#ifndef HIER_2_PAGE_TABLE_HEADER
#define HIER_2_PAGE_TABLE_HEADER

void initHier2PageTable();
int getHier2FrameIndex(unsigned page);
void setHier2FrameIndex(unsigned page, int frameIndex);
void removeHier2FrameIndex(unsigned page);
void clearHier2PageTable();

#endif
