#include <stdio.h>
#include "main.h"

#include "gpio-pb.h"
#include "mtime.h"
#include "plic.h"
#include "uart-pb.h"

unsigned char string[] = "Pa3cio, Give Me Five! \n \0";


GPIO_Registers_t *GPIO = (GPIO_Registers_t*) GPIO_BASEADDR;
UART_Registers_t *UART0 = (UART_Registers_t*) UART0_BASEADDR;
//UART_Registers_t *UART1 = (UART_Registers_t*) UART1_BASEADDR;

long cpufreq;
struct metal_cpu *cpu;



int main (void)
{

	plic_disable_all();
	plic_claim_amd_complete();		// clear CLAIM register


	init_uart(UART0, UART_1_STOP_BIT);
	// enable Receiver interrupts:
	uart_enable_rx_interrupt(UART0);



	gpio_output_en(19);
	gpio_set_pin(19);
	gpio_output_en(21);
	gpio_set_pin(21);
	gpio_output_en(22);
	gpio_set_pin(22);



	gpio_pullup_enable(GPIO, 13);
	gpio_input_enable(GPIO, 13);
	gpio_clear_all_pending(GPIO);
	gpio_low_interrupt_enable(GPIO, 13);


	plic_set_threshold(PLIC_PRIORITY_1);
	plic_set_priority(PLIC_SRC_GPIO13, PLIC_PRIORITY_6);
	plic_set_priority(PLIC_SRC_UART0, PLIC_PRIORITY_HIGHEST);


	register_handler(_vector_table, INT_MODE_VECTORED);
	enable_global_interrupts();
	enable_mtimer_interrupt();
	set_timer_compare(16384);



	plic_enable_source(PLIC_SRC_GPIO13);
	plic_enable_source(PLIC_SRC_UART0);


	enable_mexternal_interrupt();
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
