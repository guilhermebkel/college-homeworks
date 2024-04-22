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

media:          addi sp, sp, -12                # aloca espaço para 3 variáveis na pilha
                sw  a1, 0(sp)                   # salva snapshot de a1 (tamanho do vetor)
                sw  a2, 4(sp)                   # salva snapshot de a2
                sw  a3, 8(sp)                   # salva snapshot de a3
                add a2, zero, zero              # a2: soma dos elementos do vetor
sum:            lw  a3, 0(a0)                   # a3: elemento atual
                add, a2, a2, a3                 # soma elemento atual na soma total
                addi a1, a1, -1                 # decrementa quantidade de elementos processados
                addi a0, a0, 4                  # avança uma posição do vetor (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                bne a1, zero, sum               # caso não tiver processado todos os elementos, prossegue para próxima soma
                lw  a1, 0(sp)                   # recupera snapshot de a1 (tamanho do vetor)
                div a0, a2, a1                  # calcula a média
                lw  a2, 4(sp)                   # recupera snapshot de a2
                lw  a3, 8(sp)                   # recupera snapshot de a3
                addi sp, sp, 12                 # libera espaço das 3 variáveis na pilha
                jalr zero, 0(ra)                # retorna do procedimento
covariancia:    addi sp, sp, -20                # aloca espaço para 5 variáveis na pilha
                sw  a3, 0(sp)                   # salva snapshot de a3
                sw  a4, 4(sp)                   # salva snapshot de a4
                sw  a5, 8(sp)                   # salva snapshot de a5
                sw  a6, 12(sp)                  # salva snapshot de a6
                sw  a7, 16(sp)                  # salva snapshot de a7
                add a3, zero, zero              # a3: soma dos produtos da diferença
                add a4, zero, zero              # a4: quantidade de elementos processados
mult:           jal ra, media                   # calcula media dos valores do vetor 1
                add a5, a0, zero                # a5: media dos valores do vetor 1
                lw a6, 0(a0)                    # a6: elemento do vetor 1
                sub a6, a6, a5                  # a6: Xi - media(X)
                add a7, a0, zero                # a7: referência temporaria do vetor 1
                add a0, a2, zero                # adiciona vetor 2 como argumento do procedimento de media
                jal ra, media                   # calcula media dos valores do vetor 2
                add a5, a0, zero                # a5: media dos valores do vetor 2
                add a0, a7, zero                # retorna referência do vetor 1
                lw a7, 0(a2)                    # a7: elemento do vetor 2
                sub a7, a7, a5                  # a7: Yi - media(Y)
                mul a6, a6, a7                  # a6: (Xi - media(X)) * (Yi - media(Y))
                add a3, a3, a6                  # soma produto da diferença atual na soma total
                addi a4, a4, 1                  # incrementa quantidade de elementos processados
                addi a0, a0, 4                  # avança uma posição do vetor 1 (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                addi a2, a2, 4                  # avança uma posição do vetor 2 (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                bne a1, a4, mult                # caso não tiver processado todos os elementos, prossegue para próxima multiplicação
                addi a7, a1, -1                 # a7: N - 1
                div a0, a6, a7                  # calcula a covariância
                lw  a3, 0(sp)                   # recupera snapshot de a3
                lw  a4, 4(sp)                   # recupera snapshot de a4
                lw  a5, 8(sp)                   # recupera snapshot de a5
                lw  a6, 12(sp)                  # recupera snapshot de a6
                lw  a7, 16(sp)                  # recupera snapshot de a7
                addi sp, sp, 20                 # libera espaço das 5 variáveis na pilha
                jalr zero, 0(ra)                # retorna do procedimento

##### R2 END MODIFIQUE AQUI END #####

FIM: add t0, zero, s0
