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
        bne r0,t0,teste2
        addi s0,s0,1
teste2: la a0, vetor
        addi a1, zero, 10
        addi a2, zero, 3
        jal ra, multiplos
        addi t0, zero, 3
        bne r0,t0, FIM
        addi s0,s0,1
        beq zero,zero,FIM

##### R2 START MODIFIQUE AQUI START #####
multiplos:  addi a3, zero, zero             # quantidade de items checados no vetor
            addi r0, zero, zero             # quantidade de múltiplos
check:      ld a5, 0(a0)                    # elemento atual do vetor que será checado
            rem a4, a5, a2                  # resto da divisao do elemento pelo verificador
            bne a4, zero, next              # caso nao for múltiplo, evita incremento na quantidade de múltiplos
            add r0, r0, a4                  # incrementa resultado do mod na quantidade de múltiplos
next:       addi a0, a0, 8                  # avança uma posição do vetor
            addi a3, a3, 1                  # incrementa a quantidade de items checados
            blt a3, a1, check               # caso não tiver checado todos os items do vetor, continua checagem
            jalr zero, 0(ra)
##### R2 END MODIFIQUE AQUI END #####

FIM: addi t0, s0, 0