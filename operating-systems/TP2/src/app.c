#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <stdint.h>

#include "dense-page-table.h"
#include "hier-2-page-table.h"
#include "hier-3-page-table.h"
#include "inverted-page-table.h"
#include "page-replacement-algorithm.h"
#include "utils.h"
#include "app.h"

void initPageTable(PageTableType type) {
	if (type == DENSE) {
		initDensePageTable();
	} else if (type == HIER2) {
		initHier2PageTable();
	} else if (type == HIER3) {
		initHier3PageTable();
	} else if (type == INVERTED) {
		initInvertedPageTable();
	}
}

int getPageTableFrameIndex(PageTableType type, unsigned page) {
	if (type == DENSE) {
		return getDensePageTableFrameIndex(page);
	} else if (type == HIER2) {
		return getHier2PageTableFrameIndex(page);
	} else if (type == HIER3) {
		return getHier3PageTableFrameIndex(page);
	} else if (type == INVERTED) {
		return getInvertedPageTableFrameIndex(page);
	}

	return -1;
}

void setPageTableFrameIndex(PageTableType type, unsigned page, int frameIndex) {
	if (type == DENSE) {
		setDensePageTableFrameIndex(page, frameIndex);
	} else if (type == HIER2) {
		setHier2PageTableFrameIndex(page, frameIndex);
	} else if (type == HIER3) {
		setHier3PageTableFrameIndex(page, frameIndex);
	} else if (type == INVERTED) {
		setInvertedPageTableFrameIndex(page, frameIndex);
	}
}

void removePageTableFrameIndex(PageTableType type, unsigned page) {
	if (type == DENSE) {
		removeDensePageTableFrameIndex(page);
	} else if (type == HIER2) {
		removeHier2PageTableFrameIndex(page);
	} else if (type == HIER3) {
		removeHier3PageTableFrameIndex(page);
	} else if (type == INVERTED) {
		removeInvertedPageTableFrameIndex(page);
	}
}

void clearPageTable(PageTableType type) {
	if (type == DENSE) {
		clearDensePageTable();
	} else if (type == HIER2) {
		clearHier2PageTable();
	} else if (type == HIER3) {
		clearHier3PageTable();
	} else if (type == INVERTED) {
		clearInvertedPageTable();
	}
}

int getEvictedFrameIndex(ReplacementAlgorithm type, Frame* memory, unsigned numFrames) {
	if (type == RANDOM) {
		return getEvictedFrameIndexByRandom(memory, numFrames);
	} else if (type == FIFO) {
		return getEvictedFrameIndexByFIFO(memory, numFrames);
	} else if (type == LRU) {
		return getEvictedFrameIndexByLRU(memory, numFrames);
	} else if (type == LFU) {
		return getEvictedFrameIndexByLFU(memory, numFrames);
	}

	return -1;
}

Frame* initMemory(unsigned numFrames) {
	Frame* memory = malloc(sizeof(Frame) * numFrames);

	for (unsigned i = 0; i < numFrames; i++) {
		memory[i] = (Frame){
			.pageNumber = -1,
			.lastAccessTime = 0,
			.accessCount = 0,
			.dirty = 0,
			.loadTime = 0
		};
	}

	return memory;
}

TraceSimulationResult executeTraceSimulation(AppConfig appConfig) {
	TraceSimulationResult traceSimulationResult = {0, 0, 0};
	clock_t startTime = clock();

	FILE* file = fopen(appConfig.traceFilePath, "r");
	if (!file) {
		printf("Erro ao abrir o arquivo.\n");
		return traceSimulationResult;
	}

	srand(time(NULL));
	unsigned pageShiftBits = calculatePageShiftBits(appConfig.pageSizeInKB) + 10;
	unsigned address; char rw; unsigned time = 0;

	unsigned numFrames = appConfig.memorySizeInKB / appConfig.pageSizeInKB;
	Frame* memory = initMemory(numFrames);

	initPageTable(appConfig.pageTableType);

	while (fscanf(file, "%x %c", &address, &rw) != EOF) {
		traceSimulationResult.totalAccesses++;
		time++;

		unsigned page = address >> pageShiftBits;
		int frameIndex = getPageTableFrameIndex(appConfig.pageTableType, page);

		int isPageInMemory = ((frameIndex != -1) && (memory[frameIndex].pageNumber == page));

		if (isPageInMemory) {
			memory[frameIndex].lastAccessTime = time;
			memory[frameIndex].accessCount++;

			int isWriteOperation = (rw == 'W');

			if (isWriteOperation) {
				memory[frameIndex].dirty = 1;
			}
		} else {
			traceSimulationResult.pageFaults++;
			int pageHasBeenPlaced = 0;

			for (unsigned currentFrameIndex = 0; currentFrameIndex < numFrames; currentFrameIndex++) {
				int isEmptyFrame = memory[currentFrameIndex].pageNumber == -1;
				int isWriteOperation = (rw == 'W');

				if (isEmptyFrame) {
					memory[currentFrameIndex] = (Frame){
						.pageNumber = page,
						.lastAccessTime = time,
						.accessCount = 1,
						.dirty = isWriteOperation ? 1 : 0,
						.loadTime = time
					};

					setPageTableFrameIndex(appConfig.pageTableType, page, currentFrameIndex);

					pageHasBeenPlaced = 1;
					break;
				}
			}

			int isPageTableFull = !pageHasBeenPlaced;

			if (isPageTableFull) {
				int evictedFrameIndex = getEvictedFrameIndex(appConfig.replacementAlgorithm, memory, numFrames);

				if (memory[evictedFrameIndex].dirty) {
					traceSimulationResult.dirtyPages++;
				}

				removePageTableFrameIndex(appConfig.pageTableType, memory[evictedFrameIndex].pageNumber);

				int isWriteOperation = (rw == 'W');

				memory[evictedFrameIndex] = (Frame){
					.pageNumber = page,
					.lastAccessTime = time,
					.accessCount = 1,
					.dirty = isWriteOperation ? 1 : 0,
					.loadTime = time
				};

				setPageTableFrameIndex(appConfig.pageTableType, page, evictedFrameIndex);
			}
		}
	}

	fclose(file);
	free(memory);
	clearPageTable(appConfig.pageTableType);

	clock_t endTime = clock();
	traceSimulationResult.executionTimeInSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	return traceSimulationResult;
}

void generateTraceSimulationReport(const AppConfig* config, const TraceSimulationResult* result) {
	printf("Executando o simulador...\n");
	printf("Arquivo de entrada: %s\n", config->traceFilePath);
	printf("Tamanho da memória: %u KB\n", config->memorySizeInKB);
	printf("Tamanho das páginas: %u KB\n", config->pageSizeInKB);
	printf("Técnica de reposição: %s\n", getReplacementAlgorithmName(config->replacementAlgorithm));
	printf("Tipo de tabela de páginas: %s\n", getPageTableTypeName(config->pageTableType));
	printf("Páginas lidas: %u\n", result->pageFaults);
	printf("Páginas escritas: %u\n", result->dirtyPages);
	printf("Total de acessos: %u\n", result->totalAccesses);
	printf("Tempo de execução: %.6f segundos\n", result->executionTimeInSeconds);
	printf("\n");
}

int main(int argc, char* argv[]) {
	if (argc != 6) {
		printf("Uso: %s <algoritmo> <arquivo_trace> <tam_pagina_kb> <tam_memoria_kb> <tipo_tabela>\n", argv[0]);
		return 1;
	}

	AppConfig config;
	config.replacementAlgorithm = turnStringIntoReplacementAlgorithm(argv[1]);
	config.traceFilePath = argv[2];
	config.pageSizeInKB = atoi(argv[3]);
	config.memorySizeInKB = atoi(argv[4]);
	config.pageTableType = turnStringIntoPageTableType(argv[5]);

	TraceSimulationResult result = executeTraceSimulation(config);
	generateTraceSimulationReport(&config, &result);

	return 0;
}
