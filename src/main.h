/*
 * mtime.c
 *
 *  Created on: 14 Sep 2023
 *      Author: Pa3cio, UL FRI
 */


#ifndef MAIN_H
#define MAIN_H


#define MCAUSE_INT      0x80000000UL
#define MCAUSE_CAUSE    0x000003FFUL
#define MSTATUS_MIE_BIT     3  // global interrupt enable bit mask.
#define MIE_MTIE_BIT        7  // machine mode timer enable bit mask.

#define INT_MODE_DIRECT     0x00000000UL
#define INT_MODE_VECTORED   0x00000001UL



/* Timer */
void set_timer_compare(unsigned delay);


/* Interrupts : */
void _vector_table();

/* CSR Functions */
void register_handler(void *vec_table_base, unsigned int int_mode);
void enable_global_interrupts();
void enable_mtimer_interrupt();
void enable_mexternal_interrupt();

#endif /* MAIN_H */
