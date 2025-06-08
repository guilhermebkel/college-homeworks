#ifndef APP_HEADER
#define APP_HEADER

#include "utils.h"

typedef struct {
	ReplacementAlgorithm replacementAlgorithm;
	PageTableType pageTableType;
	char* traceFilePath;
	unsigned pageSizeInKB;
	unsigned memorySizeInKB;
	int debugMode;
} AppConfig;

typedef struct {
	unsigned totalAccesses;
	unsigned pageFaults;
	unsigned dirtyPages;
	double executionTimeInSeconds;
} TraceSimulationResult;

#endif
