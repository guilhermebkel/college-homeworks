#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef enum {
    LRU,
    FIFO,
    OPTIMAL, // não implementado ainda
    RANDOM,
    LFU
} ReplacementAlgorithm;

typedef struct {
    ReplacementAlgorithm replacementAlgorithm;
    char* traceFilePath;
    unsigned pageSizeInKB;
    unsigned memorySizeInKB;
} AppConfig;

typedef struct {
    unsigned totalAccesses;
    unsigned pageFaults;
    unsigned dirtyPages;
    double executionTimeInSeconds;
} TraceSimulationResult;

typedef struct {
    int pageNumber;
    unsigned lastAccessTime;
    unsigned accessCount;
    int dirty;
    unsigned loadTime;
} Frame;

ReplacementAlgorithm turnStringIntoReplacementAlgorithm(const char* str) {
    if (strcmp(str, "lru") == 0) {
        return LRU;
    } else if (strcmp(str, "fifo") == 0) {
        return FIFO;
    } else if (strcmp(str, "optimal") == 0) {
        return OPTIMAL;
    } else if (strcmp(str, "random") == 0) {
        return RANDOM;
    } else if (strcmp(str, "lfu") == 0) {
        return LFU;
    } else {
        return -1;
    }
}

const char* getReplacementAlgorithmName(ReplacementAlgorithm replacementAlgorithm) {
    switch (replacementAlgorithm) {
        case LRU:
            return "lru";
        case FIFO:
            return "fifo";
        case RANDOM:
            return "random";
        case LFU:
            return "lfu";
        case OPTIMAL:
            return "optimal (não implementado)";
        default:
            return "desconhecido";
    }
}

unsigned calculatePageShiftBits(unsigned pageSizeInKB) {
    unsigned s = 0;
    unsigned tmp = pageSizeInKB;

    while (tmp > 1) {
        tmp = tmp >> 1;
        s++;
    }

    return s;
}

int getPageToEvictByRandom(Frame* memory, unsigned numFrames) {
    return rand() % numFrames;
}

int getPageToEvictByFIFO(Frame* memory, unsigned numFrames) {
    int minLoadTime = INT_MAX;
    int index = 0;
    for (unsigned i = 0; i < numFrames; i++) {
        if (memory[i].loadTime < minLoadTime) {
            minLoadTime = memory[i].loadTime;
            index = i;
        }
    }
    return index;
}

int getPageToEvictByLRU(Frame* memory, unsigned numFrames) {
    int oldestTime = INT_MAX;
    int index = 0;
    for (unsigned i = 0; i < numFrames; i++) {
        if (memory[i].lastAccessTime < oldestTime) {
            oldestTime = memory[i].lastAccessTime;
            index = i;
        }
    }
    return index;
}

int getPageToEvictByLFU(Frame* memory, unsigned numFrames) {
    int leastAccessed = INT_MAX;
    int index = 0;
    for (unsigned i = 0; i < numFrames; i++) {
        if (memory[i].accessCount < leastAccessed) {
            leastAccessed = memory[i].accessCount;
            index = i;
        }
    }
    return index;
}

TraceSimulationResult executeTraceSimulation(AppConfig appConfig) {
    TraceSimulationResult traceSimulationResult = {0, 0, 0};
    clock_t startTime = clock();
    FILE* file = fopen(appConfig.traceFilePath, "r");

    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return traceSimulationResult;
    }

    srand(time(NULL)); // Random para RANDOM

    unsigned s = calculatePageShiftBits(appConfig.pageSizeInKB) + 10; // converte de KB para bytes
    unsigned addr;
    char rw;
    unsigned time = 0;

    unsigned numFrames = appConfig.memorySizeInKB / appConfig.pageSizeInKB;
    Frame* memory = malloc(sizeof(Frame) * numFrames);
    for (unsigned i = 0; i < numFrames; i++) {
        memory[i].pageNumber = -1;
        memory[i].lastAccessTime = 0;
        memory[i].accessCount = 0;
        memory[i].dirty = 0;
        memory[i].loadTime = 0;
    }

    while (fscanf(file, "%x %c", &addr, &rw) != EOF) {
        traceSimulationResult.totalAccesses++;
        time++;

        unsigned page = addr >> s;
        int hit = 0;

        // Verifica se a página já está na memória
        for (unsigned i = 0; i < numFrames; i++) {
            if (memory[i].pageNumber == page) {
                memory[i].lastAccessTime = time;
                memory[i].accessCount++;
                if (rw == 'W') memory[i].dirty = 1;
                hit = 1;
                break;
            }
        }

        if (!hit) {
            traceSimulationResult.pageFaults++;

            // Verifica se há espaço livre
            int placed = 0;

            for (unsigned i = 0; i < numFrames; i++) {
                if (memory[i].pageNumber == -1) {
                    memory[i].pageNumber = page;
                    memory[i].lastAccessTime = time;
                    memory[i].accessCount = 1;
                    memory[i].dirty = (rw == 'W') ? 1 : 0;
                    memory[i].loadTime = time;
                    placed = 1;
                    break;
                }
            }

            if (!placed) {
                int evictIndex;

                switch (appConfig.replacementAlgorithm) {
                    case RANDOM:
                        evictIndex = getPageToEvictByRandom(memory, numFrames);
                        break;
                    case FIFO:
                        evictIndex = getPageToEvictByFIFO(memory, numFrames);
                        break;
                    case LRU:
                        evictIndex = getPageToEvictByLRU(memory, numFrames);
                        break;
                    case LFU:
                        evictIndex = getPageToEvictByLFU(memory, numFrames);
                        break;
                    default:
                        evictIndex = 0;
                        break;
                }

                if (memory[evictIndex].dirty) {
                    traceSimulationResult.dirtyPages++;
                }

                memory[evictIndex].pageNumber = page;
                memory[evictIndex].lastAccessTime = time;
                memory[evictIndex].accessCount = 1;
                memory[evictIndex].dirty = (rw == 'W') ? 1 : 0;
                memory[evictIndex].loadTime = time;
            }
        }
    }

    fclose(file);
    free(memory);

    clock_t endTime = clock();  // termina temporizador
    traceSimulationResult.executionTimeInSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    return traceSimulationResult;
}

void generateTraceSimulationReport(const AppConfig* config, const TraceSimulationResult* traceSimulationResult) {
    printf("Executando o simulador...\n");
    printf("Arquivo de entrada: %s\n", config->traceFilePath);
    printf("Tamanho da memória: %u KB\n", config->memorySizeInKB);
    printf("Tamanho das páginas: %u KB\n", config->pageSizeInKB);
    printf("Técnica de reposição: %s\n", getReplacementAlgorithmName(config->replacementAlgorithm));
    printf("Páginas lidas: %u\n", traceSimulationResult->pageFaults);
    printf("Páginas escritas: %u\n", traceSimulationResult->dirtyPages);
    printf("Total de acessos: %u\n", traceSimulationResult->totalAccesses);
    printf("Tempo de execução: %.6f segundos\n", traceSimulationResult->executionTimeInSeconds);
    printf("\n");
}

int main(int argc, char* argv[]) {
    AppConfig appConfig;

    appConfig.replacementAlgorithm = turnStringIntoReplacementAlgorithm(argv[1]);
    appConfig.traceFilePath = argv[2];
    appConfig.pageSizeInKB = atoi(argv[3]);
    appConfig.memorySizeInKB = atoi(argv[4]);

    TraceSimulationResult traceSimulationResult = executeTraceSimulation(appConfig);

    generateTraceSimulationReport(&appConfig, &traceSimulationResult);

    return 0;
}
