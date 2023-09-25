/*
 * mtime.c
 *
 *  Created on: 14 Sep 2023
 *      Author: Pa3cio, UL FRI
 */

#include "mtime.h"

unsigned int mtime_int_flag = 0;


/*
 * This is an example of the MTIM Interrupt Handler in C
 * Use "interrupt" attribute to indicate that the specified function
 * is an interrupt handler. The compiler generates function entry
 * and exit sequences suitable for use in an interrupt handler
 * when this attribute is present.
 *
 * Sep. 2023
 * Pa3cio, UL FRI
 */

__attribute__ ((interrupt)) void mtime__handler (void) {

	volatile unsigned int mcause_value;
	// Decode interrupt cause:
	// Non memory-mapped CSR registers can only be accessed
	// using special CSR instructions. Hence, we should use
	// inline assembly:
	__asm__ volatile ("csrr %0, mcause"
	                   : "=r" (mcause_value) /* output */
	                   : /* input : none */
	                   : /* clobbers: none */);

	if (mcause_value & 0x8000007) { // mtime interrupt!
		// Increment timer compare by 1 ms:
		*MTIMECMP_ADDRESS = *MTIME_ADDRESS + 33;

		// set the flag:
		mtime_int_flag = 1;
	}

}


void mtime_delay(unsigned int miliseconds){

	for (int i=0; i<miliseconds; i++) {
		// wait for the flag from mtime interrupt handler:
		while (!mtime_int_flag) {}
		mtime_int_flag = 0;
	}
}


