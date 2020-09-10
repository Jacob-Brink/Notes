/*
* Engr220L - Lab 8
* Date: 10/25/2019
* Author: Jacob Brink
*
* This assembly code defines the BinarySearch() function 
* as explained below.  It is intended for use in Engr220L-#8
* with the associated Lab 8 main.c file.  
* 
*/




/*
    C-STYLE DECLARATION:
    int BinarySearch(int* arrayToSearchIn, int valueBeingSearchedFor, 
                     unsigned int startIndex, unsigned int endIndex);
    
    REGISTERS:
    <TODO: list the registers you use within the function here 
           including a description of each.  Hint - relate these 
           directly to the C-Code variables, parameters, etc. 
           A possible solution could use 7 registers. >
    
    CASES:
    <TODO: list the recursive and base-case options here.  This will 
           help relate the assembly and C-code.  Hint - take these 
           directly from the algorithm explained in the C-Code and 
           explain how they will operate in terms of the registers instead. >
*/

.global BinarySearch
BinarySearch:
	/*Push to stack*/
	subi sp, sp, 12
	stw ra, 0(sp)
	stw r16, 4(sp)
	stw r17, 8(sp)
	
	/*a. find middle index (r17) 0000494c*/
	sub r17, r7, r6				/*set r17 to difference of r7 and r6*/
	srli r17, r17, 1			/*divide r17 by 2 to get middle index offset from r6 start*/
	add r17, r17, r6			/*add to start index (r6)*/
	
	/*b. find middle index address (r16) */
	muli r16, r17, 0x4			/*set r16 to byte address OFFSET by multiplying the index by 4 bytes*/
	add r16, r16, r4			/*add array pointer (r8) address to OFFSET (r16)*/
	
	/*c. find middle index value (r16) */
	ldw r16, 0(r16)				/*load number at that address (r16)*/
		
	/*branch if equal*/
	beq r16, r5, Case_EQUAL			/*if middle index value (r16) is equal to r5, go to Case_A*/
	
	beq r6, r7, Case_Not_Found:
	
	/*if middle is not same as searched, continue to check if greater than or less than*/
	/*if middle index value (r16) is less than searched value (r5), search right*/
	bgt r5, r16, Skip_LESS:
	
	/*IF Searched < Middle Value*/
	Case_LESS:
	subi r7, r17, 0x1			/*subtract 1 from middle index and store in end index (r7)*/
	call BinarySearch			/*call BinarySearch with end index being one less than middle index*/
	br Start_Return
	Skip_LESS:
	
	/*IF Searched > Middle Value*/
	Case_MORE:						
	addi r6, r17, 0x1			/*set startIndex to middle index plus 1*/
	call BinarySearch			/*Call BinarySearch with startIndex at middle index plus 1*/
	br Start_Return
	Skip_MORE:	

	/*IF Middle Value == Searched*/
	Case_EQUAL:						
	add r2, r0, r17				/*set return value to r17 (middle index)*/
	br Start_Return
	
	Case_Not_Found:
	addi r2, r0, -1
	
	Start_Return:
	ldw ra, 0(sp)
	ldw r16, 4(sp)
	ldw r17, 8(sp)
	addi sp, sp, 12
	ret
	/*return*/
	
/*****************/
/* push to stack */

/* <TODO: list the registers that need to be protected on the stack 
          in a comment, then push their values onto the stack.  
          Hint - A possible solution could require 5 registers to 
          be protected, including ra. Lab7 slide deck shows an example. > */

/*****************************/
/* calculate local variables */

/* <TODO: setup the values of the registers in such a way that the 
          following code can check which of the cases we are currently in.
          Hint - this corresponds to the C-Code local variable assignments. > */

/***************/
/* check cases */

/* <TODO: check which case we are in and take the appropriate action.
          Hint - use conditional branches to "skip around" cases that we are not in.
          Hint - the action we take in each case is to set the return value and 
          then proceed to the end without checking for any other cases. > */

/******************/
/* pop from stack */

/* <TODO: list the registers that need to be protected on the stack 
          in a comment, then pop their values off the stack.  
          Hint - A possible solution could require 5 registers to 
          be protected, including ra. Lab7 slide deck shows an example. 
          Hint - this needs to happen in all cases, don't "skip around" it. > */

ret

