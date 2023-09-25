/*
 * uart0.h
 *
 *  Created on: 14 Sep 2023
 *      Author: patriciobulic
 */

#ifndef UART_PB_H_
#define UART_PB_H_

#define UART0_BASEADDR     0x10013000
#define UART1_BASEADDR     0x10023000

#define UART_1_STOP_BIT  0x0
#define UART_2_STOP_BIT  0x1


#define UART0_RX_PIN           16
#define UART0_TX_PIN           17
#define UART0_PINS_SEL         0xfffcffff  // pins 16 and 17
#define UART0_PINS_EN          0x00030000  // pins 16 and 17
#define UART1_TX_PIN           18
#define UART1_RX_PIN           23
#define UART1_PINS_SEL         0xff7bffff  // pins 18 and 23
#define UART1_PINS_EN          0x00840000  // pins 18 and 23




typedef struct
{
	volatile int UART_TXDATA;
	volatile int UART_RXDATA;
	volatile int UART_TXCTRL;
	volatile int UART_RXCTRL;
	volatile int UART_IE;
	volatile int UART_IP;
	volatile int UART_DIV;
}UART_Registers_t;

#define UART0_REGISTERS_STRUCT_POINTER ((UART_Registers_t *)UART0_BASEADDR)
#define UART1_REGISTERS_STRUCT_POINTER ((UART_Registers_t *)UART1_BASEADDR)


void uart_printf(UART_Registers_t *uart, unsigned char *string);

void uart_set_baud(UART_Registers_t *uart);
void uart_enable_tx(UART_Registers_t *uart);
void uart_enable_rx(UART_Registers_t *uart);
void uart_disable_tx(UART_Registers_t *uart);
void uart_disable_rx(UART_Registers_t *uart);
void uart_set_nstop(UART_Registers_t *uart, unsigned int nstop);
int uart_transmit_data(UART_Registers_t *uart, unsigned char data);
int uart_receive_data(UART_Registers_t *uart, unsigned char *data);
void init_uart(UART_Registers_t *uart, unsigned int nstop);
void uart_put_char(UART_Registers_t *uart, unsigned char data);
void uart_enable_rx_interrupt(UART_Registers_t *uart);
void uart_enable_tx_interrupt(UART_Registers_t *uart);




#endif /* UART_PB_H_ */
