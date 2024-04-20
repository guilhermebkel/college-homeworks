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
                add a6, zero, zero              # a6: quantidade de elementos processados
sum:            lw  a7, 0(a3)                   # a7: elemento atual
                add, a5, a5, a7                 # soma elemento atual na soma total
                addi a6, a6, 1                  # incrementa quantidade de elementos processados
                addi a3, a3, 4                  # avança uma posição do vetor (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                bne a4, a6, sum                 # caso não tiver processado todos os elementos, prossegue para próxima soma
                div a0, a5, a4                  # calcula a média
                jalr zero, 0(ra)                # retorna do procedimento
covariancia:    add a8, zero, zero              # a8: soma dos produtos da diferença
                add a9, a0, zero                # a9: vetor 1
                add a10, a2, zero               # a10: vetor 2
                add a11, a1, zero               # a11: tamanho dos vetores
                add a12, zero, zero             # a12: quantidade de elementos processados
                add a0, a9, zero                # adiciona vetor 1 como argumento do procedimento de media
                jal ra, media                   # calcula media dos valores do vetor 1
                add a15, a0, zero               # a15: media dos valores do vetor 1
                add a0, a10, zero               # adiciona vetor 2 como argumento do procedimento de media
                jal ra, media                   # calcula media dos valores do vetor 2
                add a16, a0, zero               # a16: media dos valores do vetor 2
mult:           lw a13, 0(a9)                   # a13: elemento do vetor 1
                lw a14, 0(a10)                  # a14: elemento do vetor 2
                sub a17, a13, a15               # a17: Xi - media(X)
                sub a18, a14, a16               # a18: Yi - media(Y)
                mul a19, a17, a18               # a19: (Xi - media(X)) * (Yi - media(Y))
                add a8, a8, a19                 # soma produto da diferença atual na soma total
                addi a12, a12, 1                # incrementa quantidade de elementos processados
                addi a9, a9, 4                  # avança uma posição do vetor 1 (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                addi a10, a10, 4                # avança uma posição do vetor 2 (32 bits / 8 = 4, entao incrementa de 4 em 4) 
                bne a11, a12, mult              # caso não tiver processado todos os elementos, prossegue para próxima multiplicação
                addi a20, a11, -1               # a20: N - 1
                div a0, a19, a20                # calcula a covariância
                jalr zero, 0(ra)                # retorna do procedimento

##### R2 END MODIFIQUE AQUI END #####

FIM: add t0, zero, s0
