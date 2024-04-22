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

media:          addi sp, sp, -16                # aloca espaço para 4 variáveis na pilha
                sw  a3, 0(sp)                   # salva snapshot de a3
                sw  a4, 4(sp)                   # salva snapshot de a4
                sw  a5, 8(sp)                   # salva snapshot de a5
                sw  a6, 12(sp)                  # salva snapshot de a6
                add a3, zero, zero              # a3: soma dos elementos do vetor
                add a4, a0, zero                # a4: vetor
                add a5, zero, zero              # a5: quantidade de elementos processados
sum:            lw  a6, 0(a4)                   # a6: elemento atual
                add, a3, a3, a6                 # soma elemento atual na soma total
                addi a5, a5, 1                  # incrementa quantidade de elementos processados
                addi a4, a4, 4                  # avança uma posição do vetor (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                bne a1, a5, sum                 # caso não tiver processado todos os elementos, prossegue para próxima soma
                div a0, a3, a1                  # calcula a média
                lw  a3, 0(sp)                   # recupera snapshot de a3
                lw  a4, 4(sp)                   # recupera snapshot de a4
                lw  a5, 8(sp)                   # recupera snapshot de a5
                lw  a6, 12(sp)                  # recupera snapshot de a6
                addi sp, sp, 16                 # libera espaço das 4 variáveis na pilha
                jalr zero, 0(ra)                # retorna do procedimento
covariancia:    add a8, zero, zero              # a8: soma dos produtos da diferença
                add a12, zero, zero             # a12: quantidade de elementos processados
                jal ra, media                   # calcula media dos valores do vetor 1
                add a15, a0, zero               # a15: media dos valores do vetor 1
                add a9, a0, zero                # a9: referência temporaria do vetor 1
                add a0, a2, zero                # adiciona vetor 2 como argumento do procedimento de media
                jal ra, media                   # calcula media dos valores do vetor 2
                add a16, a0, zero               # a16: media dos valores do vetor 2
                add a0, a9, zero                # retorna referência do vetor 1
mult:           lw a13, 0(a0)                   # a13: elemento do vetor 1
                lw a14, 0(a2)                   # a14: elemento do vetor 2
                sub a13, a13, a15               # a13: Xi - media(X)
                sub a14, a14, a16               # a14: Yi - media(Y)
                mul a13, a13, a14               # a13: (Xi - media(X)) * (Yi - media(Y))
                add a8, a8, a13                 # soma produto da diferença atual na soma total
                addi a12, a12, 1                # incrementa quantidade de elementos processados
                addi a0, a0, 4                  # avança uma posição do vetor 1 (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                addi a2, a2, 4                  # avança uma posição do vetor 2 (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                bne a1, a12, mult               # caso não tiver processado todos os elementos, prossegue para próxima multiplicação
                addi a14, a1, -1                # a14: N - 1
                div a0, a13, a14                # calcula a covariância
                jalr zero, 0(ra)                # retorna do procedimento

##### R2 END MODIFIQUE AQUI END #####

FIM: add t0, zero, s0
