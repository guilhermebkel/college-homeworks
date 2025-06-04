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

int getFrameIndex(PageTableType type, unsigned page) {
	if (type == DENSE) {
		return getDenseFrameIndex(page);
	} else if (type == HIER2) {
		return getHier2FrameIndex(page);
	} else if (type == HIER3) {
		return getHier3FrameIndex(page);
	} else if (type == INVERTED) {
		return getInvertedFrameIndex(page);
	}

	return -1;
}

void setFrameIndex(PageTableType type, unsigned page, int frameIndex) {
	if (type == DENSE) {
		setDenseFrameIndex(page, frameIndex);
	} else if (type == HIER2) {
		setHier2FrameIndex(page, frameIndex);
	} else if (type == HIER3) {
		setHier3FrameIndex(page, frameIndex);
	} else if (type == INVERTED) {
		setInvertedFrameIndex(page, frameIndex);
	}
}

void removeFrameIndex(PageTableType type, unsigned page) {
	if (type == DENSE) {
		removeDenseFrameIndex(page);
	} else if (type == HIER2) {
		removeHier2FrameIndex(page);
	} else if (type == HIER3) {
		removeHier3FrameIndex(page);
	} else if (type == INVERTED) {
		removeInvertedFrameIndex(page);
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

int getPageToEvict(ReplacementAlgorithm type, Frame* memory, unsigned numFrames) {
	if (type == RANDOM) {
		return getPageToEvictByRandom(memory, numFrames);
	} else if (type == FIFO) {
		return getPageToEvictByFIFO(memory, numFrames);
	} else if (type == LRU) {
		return getPageToEvictByLRU(memory, numFrames);
	} else if (type == LFU) {
		return getPageToEvictByLFU(memory, numFrames);
	}

	return -1;
}

Frame* initMemory(unsigned numFrames) {
	Frame* memory = malloc(sizeof(Frame) * numFrames);

	for (unsigned i = 0; i < numFrames; i++) {
		memory[i] = (Frame){-1, 0, 0, 0, 0};
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
	unsigned s = calculatePageShiftBits(appConfig.pageSizeInKB) + 10;
	unsigned addr; char rw; unsigned time = 0;

	unsigned numFrames = appConfig.memorySizeInKB / appConfig.pageSizeInKB;
	Frame* memory = initMemory(numFrames);

	initPageTable(appConfig.pageTableType);

	while (fscanf(file, "%x %c", &addr, &rw) != EOF) {
		traceSimulationResult.totalAccesses++;
		time++;

		unsigned page = addr >> s;
		int frameIndex = getFrameIndex(appConfig.pageTableType, page);

		if (frameIndex != -1 && memory[frameIndex].pageNumber == page) {
			memory[frameIndex].lastAccessTime = time;
			memory[frameIndex].accessCount++;

			if (rw == 'W') {
				memory[frameIndex].dirty = 1;
			}
		} else {
			traceSimulationResult.pageFaults++;
			int placed = 0;

			for (unsigned i = 0; i < numFrames; i++) {
				if (memory[i].pageNumber == -1) {
					memory[i] = (Frame){page, time, 1, (rw == 'W') ? 1 : 0, time};
					setFrameIndex(appConfig.pageTableType, page, i);
					placed = 1;
					break;
				}
			}

			if (!placed) {
				int evictIndex = getPageToEvict(appConfig.replacementAlgorithm, memory, numFrames);

				if (memory[evictIndex].dirty) {
					traceSimulationResult.dirtyPages++;
				}

				removeFrameIndex(appConfig.pageTableType, memory[evictIndex].pageNumber);

				memory[evictIndex] = (Frame){page, time, 1, (rw == 'W') ? 1 : 0, time};

				setFrameIndex(appConfig.pageTableType, page, evictIndex);
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
