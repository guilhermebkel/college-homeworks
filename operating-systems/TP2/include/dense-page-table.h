#ifndef DENSE_PAGE_TABLE_HEADER
#define DENSE_PAGE_TABLE_HEADER

void initDensePageTable ();
int getDensePageTableFrameIndex(unsigned page);
void setDenseFrameIndex(unsigned page, int frameIndex);
void removeDenseFrameIndex(unsigned page);
void clearDensePageTable();

#endif
