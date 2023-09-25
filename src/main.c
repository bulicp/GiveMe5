#include <stdio.h>
#include "main.h"

#include "gpio-pb.h"
#include "mtime.h"
#include "plic.h"
#include "uart-pb.h"

unsigned char string[] = "Pa3cio, Give Me Five! \0";


GPIO_Registers_t *GPIO = (GPIO_Registers_t*) GPIO_BASEADDR;
UART_Registers_t *UART0 = (UART_Registers_t*) UART0_BASEADDR;
//UART_Registers_t *UART1 = (UART_Registers_t*) UART1_BASEADDR;


int main (void)
{
	/*
	 * Disable all PLIC sources and vlear pending bits
	 */
	plic_disable_all();
	plic_claim_amd_complete();		// clear CLAIM register

	/*
	 * Initialize UART 0:
	 */
	init_uart(UART0, UART_1_STOP_BIT);
	// enable Receiver interrupts:
	uart_enable_rx_interrupt(UART0);

	/*
	 * Initialize GPIO LED pins:
	 */
	gpio_output_en(19);
	gpio_set_pin(19);
	gpio_output_en(21);
	gpio_set_pin(21);
	gpio_output_en(22);
	gpio_set_pin(22);


	/*
	 * Initialize GPIO interrupt input pin GPIO23 (Digital 7):
	 */
	gpio_pullup_enable(GPIO, 23);
	gpio_input_enable(GPIO, 23);
	gpio_clear_all_pending(GPIO);
	gpio_fall_interrupt_enable(GPIO, 23);


	/*
	 * Iitialize PLIC:
	 */
	plic_set_threshold(PLIC_PRIORITY_1);
	plic_set_priority(PLIC_SRC_GPIO23, PLIC_PRIORITY_HIGHEST);
	plic_set_priority(PLIC_SRC_UART0, PLIC_PRIORITY_6);
	plic_enable_source(PLIC_SRC_GPIO23);
	plic_enable_source(PLIC_SRC_UART0);


	/*
	 * Set up vectored interrupts and enable CPU's interrupts
	 */
	register_handler(_vector_table, INT_MODE_VECTORED);
	enable_global_interrupts();
	enable_mtimer_interrupt();
	enable_mexternal_interrupt();

	// set mtimecmp:
	set_timer_compare(16384);

	mtime_delay(200);

	while(1) {
		//mtime_delay(200);
		//gpio_toggle_pin(19);
		uart_printf(UART0, string);
		mtime_delay(350);
		gpio_toggle_pin(21);
		//mtime_delay(200);
		//gpio_toggle_pin(22);
	}


	return 0;
}
