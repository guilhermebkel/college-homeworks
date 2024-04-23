.data

##### R1 START MODIFIQUE AQUI START #####

vetor1: .word 1 2 3 4 #Primeiro vetor
vetor2: .word 1 1 5 5 #Segundo vetor

##### R1 END MODIFIQUE AQUI END #####
      
.text    

        add s0, zero, zero
        la a0, vetor1
        la a2, vetor2
        addi a1, zero, 4
        jal ra, covariancia
        beq zero, zero, FIM
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
                addi a0, a0, 4                  # avança uma posição do vetor 
                bne a1, zero, sum               # caso tiver mais elementos para processar, prossegue para próxima soma
                lw  a1, 0(sp)                   # recupera snapshot de a1 (tamanho do vetor)
                div a0, a2, a1                  # calcula a média
                lw  a2, 4(sp)                   # recupera snapshot de a2
                lw  a3, 8(sp)                   # recupera snapshot de a3
                addi sp, sp, 12                 # libera espaço das 3 variáveis na pilha
                jalr zero, 0(ra)                # retorna do procedimento
covariancia:    addi sp, sp, -24                # aloca espaço para 6 variáveis na pilha
                sw  ra, 0(sp)                   # salva snapshot de ra (retorno do procedimento de covariancia)
                sw  a3, 4(sp)                   # salva snapshot de a3
                sw  a4, 8(sp)                   # salva snapshot de a4
                sw  a5, 12(sp)                  # salva snapshot de a5
                sw  a6, 16(sp)                  # salva snapshot de a6
                sw  a7, 20(sp)                  # salva snapshot de a7
                add a3, zero, zero              # a3: soma dos produtos da diferença
                add a4, zero, zero              # a4: quantidade de elementos processados
mult:           add a7, a0, zero                # a7: referência temporaria do vetor 1
                jal ra, media                   # calcula media dos valores do vetor 1
                add a5, a0, zero                # a5: media dos valores do vetor 1
                add a0, a7, zero                # retorna referência do vetor 1
                slli a7, a4, 2                  # a7: offset do elemento atual do vetor
                add a7, a0, a7                  # a7: endereço do elemento atual do vetor 1
                lw a6, 0(a7)                    # a6: elemento atual do vetor 1
                sub a6, a6, a5                  # a6: Xi - media(X)
                add a7, a0, zero                # a7: referência temporaria do vetor 1
                add a0, a2, zero                # adiciona vetor 2 como argumento do procedimento de media
                jal ra, media                   # calcula media dos valores do vetor 2
                add a5, a0, zero                # a5: media dos valores do vetor 2
                add a0, a7, zero                # retorna referência do vetor 1
                slli a7, a4, 2                  # a7: offset do elemento atual do vetor
                add a7, a2, a7                  # a7: endereço do elemento atual do vetor 2
                lw a7, 0(a7)                    # a7: elemento atual do vetor 2
                sub a7, a7, a5                  # a7: Yi - media(Y)
                mul a6, a6, a7                  # a6: (Xi - media(X)) * (Yi - media(Y))
                add a3, a3, a6                  # soma produto da diferença atual na soma total
                addi a4, a4, 1                  # incrementa quantidade de elementos processados
                bne a1, a4, mult                # caso tiver mais elementos para processar, prossegue para próxima multiplicação
                addi a7, a1, -1                 # a7: N - 1
                div a0, a3, a7                  # calcula a covariância
                lw  ra, 0(sp)                   # recupera snapshot de ra (retorno do procedimento de covariancia)
                lw  a3, 4(sp)                   # recupera snapshot de a3
                lw  a4, 8(sp)                   # recupera snapshot de a4
                lw  a5, 12(sp)                  # recupera snapshot de a5
                lw  a6, 16(sp)                  # recupera snapshot de a6
                lw  a7, 20(sp)                  # recupera snapshot de a7
                addi sp, sp, 24                 # libera espaço das 6 variáveis na pilha
                jalr zero, 0(ra)                # retorna do procedimento

##### R2 END MODIFIQUE AQUI END #####

FIM: add t0, zero, s0
