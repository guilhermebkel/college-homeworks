#!/bin/bash

ALGORITHMS=("lru" "fifo" "random" "lfu")
TRACE_FILES=("./input/compilador.log" "./input/matriz.log" "./input/compressor.log" "./input/simulador.log")
PAGE_SIZES_KB_SCENARIO2=(2 4 8 16 32 64)
MEMORY_SIZES_KB_SCENARIO1=(128 256 512 1024 2048 4096 8192 16384)
PAGE_TABLE_TYPES=("densa" "hier2" "hier3" "invertida")
SIMULATOR_EXE="./bin/simulador"
OUTPUT_FILE="./output/simulation_results.csv"

# Cabeçalho do CSV
echo "Scenario,TraceFile,Algorithm,PageTableType,PageSizeKB,MemorySizeKB,TotalAccesses,PageFaults,DirtyPages,ExecutionTimeSeconds" > "$OUTPUT_FILE"

run_simulation() {
    local scenario="$1"
    local trace="$2"
    local algo="$3"
    local page_size="$4"
    local memory_size="$5"
    local pt_type="$6"

    echo "[$scenario] Executando: $trace | $algo | ${page_size}KB | ${memory_size}KB | $pt_type"

    output="$("$SIMULATOR_EXE" "$algo" "$trace" "$page_size" "$memory_size" "$pt_type")"

    total_accesses=$(echo "$output" | grep "Total de acessos:" | awk '{print $4}')
    page_faults=$(echo "$output" | grep "Páginas lidas:" | awk '{print $3}')
    dirty_pages=$(echo "$output" | grep "Páginas escritas:" | awk '{print $3}')
    exec_time=$(echo "$output" | grep "Tempo de execução:" | awk '{print $4}')

    echo "$scenario,$trace,$algo,$pt_type,$page_size,$memory_size,$total_accesses,$page_faults,$dirty_pages,$exec_time" >> "$OUTPUT_FILE"
}

# Cenário 1: Página Fixa (4KB), Memória Variável
FIXED_PAGE_SIZE_SCENARIO1=4
for trace_file in "${TRACE_FILES[@]}"; do
    for algorithm_type in "${ALGORITHMS[@]}"; do
        for page_table_type in "${PAGE_TABLE_TYPES[@]}"; do
            for memory_size in "${MEMORY_SIZES_KB_SCENARIO1[@]}"; do
                run_simulation 1 "$trace_file" "$algorithm_type" "$FIXED_PAGE_SIZE_SCENARIO1" "$memory_size" "$page_table_type"
            done
        done
    done
done

# Cenário 2: Página Variável, Memória Fixa (1024KB)
FIXED_MEMORY_SIZE_SCENARIO2=1024
for trace_file in "${TRACE_FILES[@]}"; do
    for algorithm_type in "${ALGORITHMS[@]}"; do
        for page_table_type in "${PAGE_TABLE_TYPES[@]}"; do
            for page_size in "${PAGE_SIZES_KB_SCENARIO2[@]}"; do
                run_simulation 2 "$trace_file" "$algorithm_type" "$page_size" "$FIXED_MEMORY_SIZE_SCENARIO2" "$page_table_type"
            done
        done
    done
done

echo "✅ Simulação concluída. Resultados salvos em: $OUTPUT_FILE"