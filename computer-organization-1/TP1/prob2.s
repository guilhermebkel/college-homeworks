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

media:          addi x2,x2,-16                  # x2: stack pointer
                sd x1,8(x2)
                sd x12,0(x2)
                jalr zero, 0(ra)
covariancia: jalr zero, 0(ra)

##### R2 END MODIFIQUE AQUI END #####

FIM: add t0, zero, s0
