.data

##### R1 START MODIFIQUE AQUI START #####
#
# Este espaço é para você definir as suas constantes e vetores auxiliares.
#

vetor: .word 1 2 3 4 5 6 7 8 9 10


##### R1 END MODIFIQUE AQUI END #####

.text
        add s0, zero, zero #Quantidade de testes em que seu programa passou
        la a0, vetor
        addi a1, zero, 10
        addi a2, zero, 2
        jal ra, multiplos
        addi t0, zero, 5
        bne a0,t0,teste2
        addi s0,s0,1
teste2: la a0, vetor
        addi a1, zero, 10
        addi a2, zero, 3
        jal ra, multiplos
        addi t0, zero, 3
        bne a0,t0, FIM
        addi s0,s0,1
        beq zero,zero,FIM

##### R2 START MODIFIQUE AQUI START #####
multiplos:  add a3, zero, zero              # quantidade de items checados
            add a6, zero, zero              # quantidade de múltiplos
check:      lw a5, 0(a0)                    # busca elemento atual que será checado
            rem a4, a5, a2                  # calcula o resto da divisao do elemento pelo numero verificador
            bne a4, zero, next              # caso o elemento não for múltiplo, pula o incremento da quantidade de múltiplos
            addi a6, a6, 1                  # incrementa quantidade de múltiplos
next:       addi a0, a0, 4                  # avança uma posição do vetor (32 bits / 8 = 4, entao incrementa de 4 em 4)
            addi a3, a3, 1                  # incrementa a quantidade de items checados
            bne a3, a1, check               # caso não tiver checado todos os items do vetor, continua para a checagem do proximo item
            add a0, a6, zero                # salva quantidade de múltiplos no retorno
            jalr zero, 0(ra)                # retorna do procedimento
##### R2 END MODIFIQUE AQUI END #####

FIM: addi t0, s0, 0