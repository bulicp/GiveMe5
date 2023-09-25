/*
 * uart.c
 *
 *  Created on: 14 Sep 2023
 *      Author: patriciobulic
 */

#include "uart-pb.h"

#include "gpio-pb.h"

extern GPIO_Registers_t *GPIO;

unsigned int uart_rx_data;

/*
 * ***********************************************************
 * U A R T   L O W   L E V E L   F U N C T I O N S
 * ***********************************************************
 */


/*
 * Set Baud Rate to 115200
 * With tlclk at 16Mhz, to achieve 115200 baud,
 *  divisor should be 139. SiFive FE310-G002 Manual:, page 85
 * @arguments:
 * 	uart: UART0 or UART1
 */
void uart_set_baud(UART_Registers_t *uart){
	uart->UART_DIV = 139;
}

/*
 * Enable TX
 * @arguments:
 * 	uart: UART0 or UART1
 */
void uart_enable_tx(UART_Registers_t *uart){
	uart->UART_TXCTRL |= 0x00000001;
}

/*
 * Disable TX
 * @arguments:
 * 	uart: UART0 or UART1
 */
void uart_disable_tx(UART_Registers_t *uart){
	uart->UART_TXCTRL &= 0xfffffffe;
}

/*
 * Enable RX
 * @arguments:
 * 	uart: UART0 or UART1
 */
void uart_enable_rx(UART_Registers_t *uart){
	uart->UART_RXCTRL |= 0x00000001;
}

/*
 * Disable RX
 * @arguments:
 * 	uart: UART0 or UART1
 */
void uart_disable_rx(UART_Registers_t *uart){
	uart->UART_RXCTRL &= 0xfffffffe;
}

/*
 * Set No. stop bits
 * @arguments:
 *  uart: UART0 or UART1
 * 	nstop: UART_1_STOP_BIT or UART_2_STOP_BIT
 */
void uart_set_nstop(UART_Registers_t *uart, unsigned int nstop){

	if (nstop == UART_1_STOP_BIT) {
		uart->UART_RXCTRL &= 0xfffffffd;
	}
	else if (nstop == UART_2_STOP_BIT) {
		uart->UART_RXCTRL |= 0x00000002;
	}
}


/*
 * Init uart
 * @arguments:
 * 	uart: UART0 or UART1
 */
void init_uart(UART_Registers_t *uart, unsigned int nstop){

	// select and enable IO FUNC
	if (uart == (UART_Registers_t*) UART0_BASEADDR){
		GPIO->GPIO_IOF_SEL &= UART0_PINS_SEL;
		GPIO->GPIO_IOF_EN |= UART0_PINS_EN;
	}
	if (uart == (UART_Registers_t*) UART1_BASEADDR){
		GPIO->GPIO_IOF_SEL &= UART1_PINS_SEL;
		GPIO->GPIO_IOF_EN |= UART1_PINS_EN;
	}

	uart_set_baud(uart);
	uart_enable_tx(uart);
	uart_enable_rx(uart);
	uart_set_nstop(uart, nstop);
}

/*
 * Transmit data
 * @arguments:
 * 	uart: UART0 or UART1
 * 	data: data to transmit
 * @ return: 0 - success
 * 			 1 - error
 */
int uart_transmit_data(UART_Registers_t *uart, unsigned char data){
	// Reading from txdata returns the current value of
	// the full flag and zero in the data field
	if (uart->UART_TXDATA == 0)  {// transmit FIFO able to accept new entry
		uart->UART_TXDATA = data;
		return 0;
	}

	// Transmit FIFO full:
	return 1;
}

/*
 * Receive data
 * @arguments:
 * 	uart: UART0 or UART1
 * 	data: received data if FIFO contains a valid character
 * @ return: 0 - success
 * 			 1 - error
 */
 int uart_receive_data(UART_Registers_t *uart, unsigned char *data){

	unsigned int rxdata;

	rxdata = (uart->UART_RXDATA);

	// The empty flag indicates if the receive FIFO was empty.
	//  when set, the data field does not contain a valid character.
	if (rxdata & 0x80000000)  {// Receive FIFO empty
		return 1;
	}

	*data = (unsigned char) rxdata;
	return 0;

}


 /*
   * ***********************************************************
   * U A R T   I N T E R R U P T   F U N C T I O N S
   * ***********************************************************
   */

 /*
  * Enable Receive watermark interrupt
  * @arguments:
  * 	uart: UART0 or UART1
  */
 void uart_enable_rx_interrupt(UART_Registers_t *uart){
 	uart->UART_IE |= 0x00000002;
 }


/*
 * Enable Transmit watermark interrupt
 * @arguments:
 * 	uart: UART0 or UART1
 */
void uart_enable_tx_interrupt(UART_Registers_t *uart){
  	uart->UART_IE |= 0x00000001;
}



/*
 * UART handler
 */
 void _uart0_handler(){

	 // if Receive watermark interrupt pending:
	 if (UART0_REGISTERS_STRUCT_POINTER->UART_IP & 0x00000002){
		 uart_rx_data = UART0_REGISTERS_STRUCT_POINTER->UART_RXDATA;
	 }

	 // if Transmit watermark interrupt pending:
	 if (UART0_REGISTERS_STRUCT_POINTER->UART_IP & 0x00000001){
		 // TODO: transmit code goes here
	 }
 }






 /*
  * ***********************************************************
  * U A R T   U T I L I T Y   F U N C T I O N S
  * ***********************************************************
  */



/*
 * Try to put a char until success
 * @arguments:
 * 	uart: UART0 or UART1
 *  data: char to send
 */
void uart_put_char(UART_Registers_t *uart, unsigned char data){
	unsigned int txdata_reg;
	// Reading from txdata returns the current value of
	// the full flag and zero in the data field
	// wait untul ready to accept new data.
	do {
		txdata_reg = uart->UART_TXDATA;
	}
	while (txdata_reg & 0x80000000);

	// transmit FIFO able to accept new entry
	uart->UART_TXDATA = data;
}

/*
 * Send null-terminated string over UART
 *
 * @arguments:
 * 	uart: UART0 or UART1
 *  string: null-terminated string to send
 */
void uart_printf(UART_Registers_t *uart, unsigned char *string){

	unsigned char data = string[0];
	int i = 0;

	while (data != '\0'){
		uart_put_char(uart, data);
		i++;
		data = string[i];
	}
}



