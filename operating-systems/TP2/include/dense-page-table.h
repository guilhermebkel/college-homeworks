#ifndef DENSE_PAGE_TABLE_HEADER
#define DENSE_PAGE_TABLE_HEADER

void initDensePageTable ();
int getDensePageTableFrameIndex(unsigned page);
void setDensePageTableFrameIndex(unsigned page, int frameIndex);
void removeDensePageTableFrameIndex(unsigned page);
void clearDensePageTable();

#endif
