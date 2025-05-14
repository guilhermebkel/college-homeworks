#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LRU,
    FIFO,
    OPTIMAL
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
} TraceSimulationResult;

ReplacementAlgorithm turnStringIntoReplacementAlgorithm(const char* str) {
    if (strcmp(str, "lru") == 0) {
        return LRU;
    } else if (strcmp(str, "fifo") == 0) {
        return FIFO;
    } else if (strcmp(str, "optimal") == 0) {
        return OPTIMAL;
    } else {
        return -1;
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

TraceSimulationResult processTraceFile(const char* fileName, unsigned pageSizeInKB) {
    TraceSimulationResult traceSimulationResult = {0, 0, 0};
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return traceSimulationResult;
    }

    unsigned s = calculatePageShiftBits(pageSizeInKB);
    unsigned addr;
    char rw;

    while (fscanf(file, "%x %c", &addr, &rw) != EOF) {
        traceSimulationResult.totalAccesses++;  // Contabiliza o acesso à memória

        // Calcular a página (descartar os s bits menos significativos do endereço)
        unsigned page = addr >> s;

        // Simular page fault e página suja
        if (rw == 'W') {
            traceSimulationResult.dirtyPages++;  // Página "suja" (escrita)
        }

        // Para simplificar, vamos assumir que a cada novo acesso a uma página ocorre um page fault
        traceSimulationResult.pageFaults++;  // Assumindo que sempre há um page fault para esse exemplo
    }

    fclose(file);

    return traceSimulationResult;
}

void generateTraceSimulationReport(const AppConfig* config, const TraceSimulationResult* traceSimulationResult) {
    printf("Executando o simulador...\n");
    printf("Arquivo de entrada: %s\n", config->traceFilePath);
    printf("Tamanho da memória: %u KB\n", config->memorySizeInKB);
    printf("Tamanho das páginas: %u KB\n", config->pageSizeInKB);
    printf("Técnica de reposição: %s\n", 
        (config->replacementAlgorithm == LRU) ? "lru" :
        (config->replacementAlgorithm == FIFO) ? "fifo" : "optimal");
    printf("Páginas lidas: %u\n", traceSimulationResult->totalAccesses);
    printf("Páginas escritas: %u\n", traceSimulationResult->dirtyPages);
}

int main(int argc, char* argv[]) {
    AppConfig config;
    config.replacementAlgorithm = turnStringIntoReplacementAlgorithm(argv[1]);
    config.traceFilePath = argv[2];
    config.pageSizeInKB = atoi(argv[3]);
    config.memorySizeInKB = atoi(argv[4]);

    TraceSimulationResult traceSimulationResult = processTraceFile(config.traceFilePath, config.pageSizeInKB);

    generateTraceSimulationReport(&config, &traceSimulationResult);

    return 0;
}
