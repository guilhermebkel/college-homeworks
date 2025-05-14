#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LRU,
    FIFO,
    OPTIMAL
} ReplacementAlgorithm;

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

unsigned calculateShiftBits(unsigned pageSizeInKB) {
    unsigned s = 0;
    unsigned tmp = pageSizeInKB;

    while (tmp > 1) {
        tmp = tmp >> 1;
        s++;
    }

    return s;
}

// Função para processar o arquivo de trace
void processTraceFile(const char* fileName, unsigned pageSizeInKB) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    unsigned s = calculateShiftBits(pageSizeInKB);
    unsigned addr;
    char rw;

    // Lendo o arquivo linha por linha
    while (fscanf(file, "%x %c", &addr, &rw) != EOF) {
        // Calcular a página (descartar os s bits menos significativos do endereço)
        unsigned page = addr >> s;

        printf("Endereço: %x, Operação: %c, Página: %x\n", addr, rw, page);
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    ReplacementAlgorithm replacementAlgorithm = turnStringIntoReplacementAlgorithm(argv[1]);
    char* traceFilePath = argv[2];
    int pageSizeInKB = atoi(argv[3]);
    int memorySizeInKB = atoi(argv[4]);

    processTraceFile(traceFilePath, pageSizeInKB);

    return 0;
}
