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

/* TODO: initialize the timer with the proper timeout period */

MAIN_PROG:  
addi r15, r0, 0x40000
movia r17, LEDR_BASE

add r16, r0, r0

LOOP_TOP:
addi r16, r16, 0x1
stwio r16, 0(r17)
blt r16, r15, LOOP_TOP


MAIN_PROG_END:
    /* infinite loop to keep out of global memory, useful for final breakpoint */
    br MAIN_PROG_END

/****************/
/* DATA SECTION */
/****************/
.data

/* if any global variables are needed, place them here */

.end
