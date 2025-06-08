#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

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

void printDebugMessage(AppConfig appConfig, const char* format, ...) {
	if (appConfig.debugMode) {
		va_list args;
		va_start(args, format);

		printf("[DEBUG] ");
		vprintf(format, args);

		va_end(args);
	}
}

Frame* initMemory(unsigned numFrames) {
	Frame* memory = malloc(sizeof(Frame) * numFrames);

	for (unsigned frameIndex = 0; frameIndex < numFrames; frameIndex++) {
		memory[frameIndex] = (Frame){
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
	unsigned address;
	char rw;
	unsigned time = 0;

	unsigned numFrames = appConfig.memorySizeInKB / appConfig.pageSizeInKB;
	Frame* memory = initMemory(numFrames);

	initPageTable(appConfig.pageTableType);

	while (fscanf(file, "%x %c", &address, &rw) != EOF) {
		traceSimulationResult.totalAccesses++;
		time++;

		unsigned page = address >> pageShiftBits;
		int frameIndex = getPageTableFrameIndex(appConfig.pageTableType, page);

		int isPageInMemory = ((frameIndex != -1) && (memory[frameIndex].pageNumber == page));

		printDebugMessage(appConfig, "Tempo %u: Acesso ao endereco 0x%x (%c) -> Pagina Virtual %u\n", time, address, rw, page);

		if (isPageInMemory) {
			printDebugMessage(appConfig, "ACERTO (HIT): Pagina %u encontrada no Quadro %d.\n", page, frameIndex);

			memory[frameIndex].lastAccessTime = time;
			memory[frameIndex].accessCount++;

			int isWriteOperation = (rw == 'W');

			if (isWriteOperation) {
				memory[frameIndex].dirty = 1;

				printDebugMessage(appConfig, "Operacao de ESCRITA: Quadro %d marcado como SUJO.\n", frameIndex);
			}
		} else {
			traceSimulationResult.pageFaults++;

			printDebugMessage(appConfig, "FALHA DE PAGINA (PAGE FAULT): Pagina %u nao esta na memoria.\n", page);

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

					printDebugMessage(appConfig, "Pagina %u carregada no Quadro VAZIO %u.\n", page, currentFrameIndex);

					if (isWriteOperation) {
						printDebugMessage(appConfig, "Operacao de ESCRITA: Quadro %u marcado como SUJO.\n", currentFrameIndex);
					}

					pageHasBeenPlaced = 1;
					break;
				}
			}

			int isPageTableFull = !pageHasBeenPlaced;

			if (isPageTableFull) {
				int evictedFrameIndex = getEvictedFrameIndex(appConfig.replacementAlgorithm, memory, numFrames);
				unsigned evictedPage = memory[evictedFrameIndex].pageNumber;
				int isPageDirty = memory[evictedFrameIndex].dirty;

				printDebugMessage(appConfig, "Memoria CHEIA. Algoritmo %s selecionou Quadro %d para substituicao (Pagina %u).\n", getReplacementAlgorithmName(appConfig.replacementAlgorithm), evictedFrameIndex, evictedPage);

				if (isPageDirty) {
					traceSimulationResult.dirtyPages++;
					printDebugMessage(appConfig, "Pagina %u (Quadro %d) estava SUJA e sera ESCRITA de volta no disco.\n", evictedPage, evictedFrameIndex);
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

				printDebugMessage(appConfig, "Pagina %u carregada no Quadro %d.\n", page, evictedFrameIndex);

				if (isWriteOperation) {
					printDebugMessage(appConfig, "Operacao de ESCRITA: Quadro %d marcado como SUJO.\n", evictedFrameIndex);
				}
			}
		}

		printDebugMessage(appConfig, "----------------------------------\n\n");
	}

	fclose(file);
	free(memory);
	clearPageTable(appConfig.pageTableType);

	clock_t endTime = clock();
	traceSimulationResult.executionTimeInSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	return traceSimulationResult;
}

void generateTraceSimulationReport(const AppConfig* config, const TraceSimulationResult* result) {
	printf("=> Resultado da simulação:\n");
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
	AppConfig appConfig;
	appConfig.replacementAlgorithm = turnStringIntoReplacementAlgorithm(argv[1]);
	appConfig.traceFilePath = argv[2];
	appConfig.pageSizeInKB = atoi(argv[3]);
	appConfig.memorySizeInKB = atoi(argv[4]);
	appConfig.pageTableType = turnStringIntoPageTableType(argv[5]);
	appConfig.debugMode = argc == 7 ? 1 : 0;

	TraceSimulationResult result = executeTraceSimulation(appConfig);
	generateTraceSimulationReport(&appConfig, &result);

	return 0;
}
