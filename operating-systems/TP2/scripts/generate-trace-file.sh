#!/bin/bash
OUTPUT_FOLDER="./input"
TOTAL_ACCESSES=1000
READ_OPERATIONS_PERCENTAGE=60

# Função para gerar acessos com base no padrão
generate_trace_file() {
    local ACCESS_PATTERN=$1
    local OUTPUT_FILE_PATH=$2

    echo "Gerando $TOTAL_ACCESSES acessos com padrão: $ACCESS_PATTERN -> $OUTPUT_FILE_PATH"

    > "$OUTPUT_FILE_PATH"

    for ((i=0; i<TOTAL_ACCESSES; i++)); do
        case "$ACCESS_PATTERN" in
            sequential)
                address=$(printf "%08x" $((0x00000000 + i * 4)))
                ;;
            random)
                address=$(printf "%08x" $((RANDOM << 16 | RANDOM)))
                ;;
            spatial_locality)
                # Muitos acessos em regiões próximas (baixa variação)
                base=$((0x20000000))
                offset=$((RANDOM % 1024 * 4))
                address=$(printf "%08x" $((base + offset)))
                ;;
            temporal_locality)
                # Repete endereços recentes com alta frequência
                if (( RANDOM % 10 < 8 && i > 10 )); then
                    j=$((RANDOM % 10))
                    address=$(sed -n "$((i - j))p" "$OUTPUT_FILE_PATH" | cut -d ' ' -f1)
                else
                    address=$(printf "%08x" $((RANDOM << 16 | RANDOM)))
                fi
                ;;
            *)
                echo "Padrão desconhecido: $ACCESS_PATTERN"
                return
                ;;
        esac

        # Define operação com base na porcentagem de leitura
        if (( RANDOM % 100 < READ_OPERATIONS_PERCENTAGE )); then
            op="R"
        else
            op="W"
        fi

        echo "$address $op" >> "$OUTPUT_FILE_PATH"
    done

    echo "Arquivo '$OUTPUT_FILE_PATH' gerado com sucesso!"
    echo
}

generate_trace_file "sequential" "$OUTPUT_FOLDER/simulacao_acesso_sequencial.log"
generate_trace_file "random" "$OUTPUT_FOLDER/simulacao_acesso_aleatorio.log"
generate_trace_file "spatial_locality" "$OUTPUT_FOLDER/simulacao_localidade_espacial.log"
generate_trace_file "temporal_locality" "$OUTPUT_FOLDER/simulacao_localidade_temporal.log"
