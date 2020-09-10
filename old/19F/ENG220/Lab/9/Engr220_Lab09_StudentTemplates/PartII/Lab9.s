/*
* Engr220L - Lab 9
* Date: <TODO>
* Author: <TODO>
*
* <TODO describe the program summary>
* 
*/

/************/
/* INCLUDES */
/************/
.include "nios_macros.s"
.include "nios_defs.s"   /* .equ statements specific to this system */

/*************/
/* CONSTANTS */
/*************/
.equ MS100,     5000000    /* number of clock cycles in 100 msec provided as example */
.equ MS100LOW,  0x4b40     /* 16 least signif bits */
.equ MS100HIGH, 0x4c       /* 16 most signif bits */

/****************/
/* TEXT SECTION */
/****************/
.text
/* Place the main routine at the reset address */
.org RESET_VECTOR 

/* Program start location must be identified */
.global _start
_start:

/*********************/
/* MAIN PROGRAM CODE */
/*********************/

MAIN_PROG_INIT:
  
/* TODO: initialize PIO devices if needed */



MAIN_PROG:  
movia r17, LEDR_BASE
.equ TIME_CYCLES, 0x17D783F
.equ TIME_OUT_MASK, 0x1

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

/* Turn on CONT bit and START bit in control_OFFSET */
addi r10, r0, 0b110
stwio r10, CONTROL_OFFSET(gp)

/*movia r18, r0, 0x1  r9 is mask to get timeout bit */

/* initialize r16 (loop counter) to 0*/
add r16, r0, r0
movia r15, 0x40000

RESTART_TIMER:
stwio r0, STATUS_OFFSET(gp)
br LOOP_TOP

LOOP_TOP:
/* increment counter and leds */
addi r16, r16, 0x1
stwio r16, 0(r17)

/*delay, loop until some time out bit goes to one*/
DELAY_LOOP:
ldwio r10, STATUS_OFFSET(gp)
andi r10, r10, TIME_OUT_MASK
bgt r10, r0, RESTART_TIMER
br DELAY_LOOP

blt r16, r15, LOOP_TOP


br MAIN_PROG


MAIN_PROG_END:
    /* infinite loop to keep out of global memory, useful for final breakpoint */
    br MAIN_PROG_END

/****************/
/* DATA SECTION */
/****************/
.data

/* if any global variables are needed, place them here */

.end
