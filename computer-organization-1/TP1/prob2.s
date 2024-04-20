.data

##### R1 START MODIFIQUE AQUI START #####

vetor1: .word 1 2 3 4 #Primeiro vetor
vetor2: .word 1 1 1 1 #Segundo vetor

##### R1 END MODIFIQUE AQUI END #####
      
.text    

        add s0, zero, zero
        la a0, vetor1
        addi a1, zero, 4
        jal ra, media
        addi t0, zero, 2
        bne a0,t0,teste2
        addi s0,s0,1
teste2: la a0, vetor2
        addi a1, zero, 4
        jal ra, media
        addi t0, zero, 1
        bne a0,t0, FIM
        addi s0,s0,1
        beq zero,zero, FIM

##### R2 START MODIFIQUE AQUI START #####

media:          add a5, zero, zero              # a5: soma dos elementos do vetor
                add a3, a0, zero                # a3: vetor
                add a4, a1, zero                # a4: quantidade de elementos do vetor
                add a6, zero, zero              # a6: quantidade de elementos somados
sum:            lw  a7, 0(a3)                   # busca o elemento atual que será somado na soma total
                add, a5, a5, a7                 # soma elemento atual na soma total
                addi a6, a6, 1                  # incrementa quantidade de elementos somados
                addi a3, a3, 4                  # avança uma posição do vetor (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                bne a4, a6, sum                 # caso não tiver somado todos os elementos, prossegue para próxima soma
                div a0, a5, a4                  # faz a divisao da soma de elementos pela quantidade de elementos
                jalr zero, 0(ra)                # retorna do procedimento
covariancia:    jalr zero, 0(ra)                # retorna do procedimento

##### R2 END MODIFIQUE AQUI END #####

FIM: add t0, zero, s0
