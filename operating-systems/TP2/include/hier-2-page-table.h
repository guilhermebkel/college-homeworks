#ifndef HIER_2_PAGE_TABLE_HEADER
#define HIER_2_PAGE_TABLE_HEADER

void initHier2PageTable();
int getHier2PageTableFrameIndex(unsigned page);
void setHier2PageTableFrameIndex(unsigned page, int frameIndex);
void removeHier2PageTableFrameIndex(unsigned page);
void clearHier2PageTable();

#endif
