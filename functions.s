@ functions.s





/* This function aids in the process of incementing the difficulty of the game.  */
.global	increment_speed
increment_speed:
    add r0, r0, #1      @ increment r0 
    mov r1,#120         @ move 120 into r1
    cmp r0,r1           @ compare r0 and r1
    beq .setZero        @ branch to .setBackTo0
    b .done             @ branch to .done

.setZero:
    mov r0, #0          @ move 0 back into r0 
    b .done
.done:
    mov pc, lr          @ return value to user




/* This function serves as a countdown timer for each game. */
.global	countDown
countDown:
    
    cmp r0, r3          @ compare r0 and r3      
    blt .setTwo         @ branch to .setTwo if less than

    mov r0, #3          @ move 3 into r0 
    b .end

.setTwo:
    cmp r0, r2
    blt .setOne

    mov r0, #2
    b .end


.setOne:
    cmp r0, r1
    blt .set_Zero

    mov r0, #1
    b .end
   

.set_Zero:
    mov r0, #0
    b .end


.end:
     mov pc, lr          @ return value to user
    
