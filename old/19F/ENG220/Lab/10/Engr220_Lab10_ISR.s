/*
* Engr220L - Lab 10
* Date: 11/8/2019
* Author: Jacob Brink
*
* <TODO describe the program summary>
* 
*/

/************/
/* INCLUDES */
/************/
.include "nios_macros.s"
.include "nios_defsISR.s" /* system specific definitions */

/*************/
/* CONSTANTS */
/*************/
/* TODO: add your own .equ statements here */

/****************/
/* TEXT SECTION */
/****************/
.text
/* Place the main routine at the reset address */
.org RESET_VECTOR

/* Program start location must be identified */
.global _start
_start:

/* jump over the ISR code in order to begin execution at MAIN_PROG_INIT */
br MAIN_PROG_INIT

/************/
/* ISR CODE */
/************/
/* ISR = Interrupt Service Routine */

/* The following happens when an external interrupt occurs:  The cpu:
   1. Copies the contents of the status register (ctl0) to estatus
      (ctl1) saving the processor’s pre-exception status
   2. Clears the U bit of the status register, forcing the processor 
      into supervisor mode
   3. Clears the PIE bit of the status register, disabling external
      processor interrupts
   4. Writes the address of the instruction after the exception to 
      the ea register (r29)
   5. Transfers execution to the address of the exception handler that
      determines the cause of the interrupt
*/
.org EXCEPTION_VECTOR
ISR:
	subi sp, sp, 12
	stw r10, 0(sp)
	stw r11, 4(sp)
	stw r12, 8(sp)
	
    /* these three lines of code should not be changed */
    rdctl et, ctl4 /* Check if an external (hardware) intr has occurred */
    beq et, r0, EXCEPTION_ACTION 
    subi ea, ea, 4 /* If yes, decrement ea to re-execute interrupted  
                      instruction when you return from the ISR */

EXCEPTION_ACTION:
/* The interrupt-service/exception-handler routine: After determining
   the source of the interrupt, the interrupt condition must be cleared.
   Note that if any register besides r0, et, ea, and sp are used, they must
   first be pushed on the stack and then pulled off the stack before
   returning from the interrupt (eret). */

    /* TODO: push to stack any registers that will change (except as noted above) */
    /*       it is also allowable to push and pop for just certain cases of the ISR */
   
CHECK_FOR_INTR_0:
/* TODO: check if intr 0 needs service by checking bit 0 of ipending (ctl4). */
rdctl r11, ctl4
andi r10, r11, 0b1
beq r10, r0, CHECK_FOR_INTR_1

/* TODO: this should execute every time the ISR is called, even if another check-#==yes */

RESPOND_TO_INTR_0:
/* TODO: The interrupt 0 action goes here, this should only execute if check-0==yes */
stwio r0, STATUS_OFFSET(gp)
addi r10, r0, 0x40000
ldwio r12, COUNTER_HERO(r0)
blt r12, r10, SKIP_RESET
add r12, r0, r0
SKIP_RESET:
addi r12, r12, 0x1
movia r17, LEDR_BASE
stwio r12, 0(r17)
stwio r12, COUNTER_HERO(r0)


CHECK_FOR_INTR_1:
/* TODO: check if intr 1 needs service by checking bit 1 of ipending (ctl4). */
/* TODO: this should execute every time the ISR is called, even if another check-#==yes */
rdctl r11, ctl4
movi r12, KEY_MASK
and r10, r11, r12
beq r10, r0, END_ISR

RESPOND_TO_INTR_1:
/* TODO: The interrupt 1 action goes here, this should only execute if check-1==yes */
/* clear EDGE register */
movia r11, KEY_BASE
stwio r0, EDGE_OFFSET(r11)
/* set period h to sw something idk really tbh  plz help me */
movia r12, SW_BASE
ldwio r11, 0(r12)
stwio r11, PERIODH_OFFSET(gp)
/* restart timer */
/* Turning on START, CONT, and ITO bit to be on */
addi r10, r0, 0b111
stwio r10, CONTROL_OFFSET(gp)





CHECK_FOR_INTR_2:
/* TODO: check if intr 2 needs service by checking bit 2 of ipending (ctl4). */
/* TODO: this should execute every time the ISR is called, even if another check-#==yes */

RESPOND_TO_INTR_2:
/* TODO: The interrupt 2 action goes here, this should only execute if check-2==yes */

/* The cpu does the following when you return from the interrupt:  
   1. Copies contents of estatus (ctl1) to status (ctl0) (restores it).
   2. Transfers program execution to the address in ea register (r29)
      by copying what is in ea to the program counter (pc).
   NOTE: If you pushed any registers on the stack, pop them off now. */
END_ISR:
    /* TODO: pop from stack anything that was pushed */
    ldw r10, 0(sp)
	ldw r11, 4(sp)
	ldw r12, 8(sp)
	addi sp, sp, 12
	eret /* Return from exception */
	
/****************/
/* END ISR CODE */
/****************/

/*********************/
/* MAIN PROGRAM CODE */
/*********************/

MAIN_PROG_INIT:
/* TODO: the main program startup code goes here */

    SP_INIT:
    /* TODO: initialize stack pointer if needed */
	movia sp, 0x7fff

    GLOBAL_VARIABLES_INIT:
    /* TODO: initialize global variables if needed */
	stwio r0, COUNTER_HERO(r0)
	
    IO_BASE_INIT:
    /* TODO: setup registers with I/O base addresses if needed */

    IO_DEVICE_INIT:
    /* TODO: initialize PIO devices if needed */

    TIMER_INIT:
    /* TODO: initialize the timers if needed */

	.equ TIME_CYCLES, 0x17D783F

	/* initialize the timer with the proper timeout period */
	movia r10, TIME_CYCLES /* PERIOD (clock ticks for .5 seconds) */
	movia gp, TIMER_BASE
	
	/* initialize PERIODH and PERIODL to PERIOD */
	addi r10, r0, 0x17D
	stwio r10, PERIODH_OFFSET(gp)
	addi r10, r0, 0x783F
	stwio r10, PERIODL_OFFSET(gp)

	/* Turn on RUN bit in status_control */
	stwio r0, STATUS_OFFSET(gp)

	/* Turn on CONT bit and START bit in control_OFFSET 
	addi r10, r0, 0b110 COMMENTED OUT OUT OUT OUT
	stwio r10, CONTROL_OFFSET(gp) OUT OUT OUT OUT
	*/



    SET_PORT_INTR:
    /* TODO: Setup all I/O ports for interrupts: */
    /* 1) clear the intr flag in each port and */
    /* 2) turn interrupts on in each port. */
	stwio r0, STATUS_OFFSET(gp)
	/* Turning on START, CONT, and ITO bit to be on */
	addi r10, r0, 0b111
	stwio r10, CONTROL_OFFSET(gp)
	
	/* 1.a */
	movia r11, KEY_BASE
	stwio r0, EDGE_OFFSET(r11)
	/* 1.b */
	movi r10, 0x4
	stwio r10, MASK_OFFSET(r11)
	
	

    SET_IENABLE:
        /* TODO: enable each interrupt in the IENABLE reg */
        /*       Set the IENABLE for control register # as needed, */
        /*       ctl3 is shown as an example */
        
        /* Set the IENABLE for control register 3 */
        rdctl et, ctl3 /* Read the interrupt enable register = ctrl_reg3 */
        ori et, et, TIMER_MASK  /* set the timer interrupt enable bit high */
		ori et, et, KEY_MASK /* 2: set interrupt for button */
        /* TODO: use additional ori instructions to turn on other interrupts */
        wrctl ctl3, et  /* write the final pattern back to IENABLE (ctl3) */
		
		

    SET_STATUS:
        /* Now enable interrupts globally in the processor status register. */
        rdctl et, ctl0 /* Read the status register = ctrl_reg0 */
        ori et, et, PIE_MASK  /* set the PIE bit to enable all interrupts */
        wrctl ctl0, et  /* write the pattern back to STATUS (ctl0) */

/* End MAIN_PROG_INIT */
/*********************/

MAIN_PROG:
/* TODO  write main program functionality as needed here */
DO_NOTHING:
br DO_NOTHING

MAIN_PROG_END:
    /* infinite loop to keep out of global memory, useful for final breakpoint */
    br MAIN_PROG_END  

/*************************/
/* END MAIN PROGRAM CODE */
/*************************/

/****************/
/* DATA SECTION */
/****************/
.data
/* TODO: if needed, add .word or .skip declarations here for global variables */

/* TODO replace MYGLOBALVAR with whichever global variable(s) you need*/
COUNTER_HERO:     /* "MYGLOBALVAR" is considered the name of the global var */
    .word 0      /* allocate 4 bytes and initialize them to 0 */

.end


