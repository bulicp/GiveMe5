/*
 * gpio.c
 *
 *  Created on: 24 Sep 2023
 *      Author: patriciobulic
 */

#include "gpio-pb.h"
#include "plic.h"

void gpio_input_enable(GPIO_Registers_t *GPIO, unsigned int pin) {
	GPIO->GPIO_INPUT_EN |= (1 << pin);
}

void gpio_output_enable(GPIO_Registers_t *GPIO, unsigned int pin) {
	GPIO->GPIO_OUTPUT_EN |= (1 << pin);
}

void gpio_toggle(GPIO_Registers_t *GPIO, unsigned int pin) {
	GPIO->GPIO_OUTPUT_EN ^= (1 << pin);
}



void gpio_pullup_enable(GPIO_Registers_t *GPIO, unsigned int pin) {
	GPIO->GPIO_PUE |= (1 << pin);
}

void gpio_high_interrupt_enable(GPIO_Registers_t *GPIO, unsigned int pin) {
	GPIO->GPIO_HIGH_IE |= (1 << pin);

	// disable all others on that pin:
	GPIO->GPIO_LOW_IE &= ~(1 << pin);
	GPIO->GPIO_FALL_IE &= ~(1 << pin);
	GPIO->GPIO_RISE_IE &= ~(1 << pin);
}

void gpio_low_interrupt_enable(GPIO_Registers_t *GPIO, unsigned int pin) {
	GPIO->GPIO_LOW_IE |= (1 << pin);

	// disable all others on that pin:
	GPIO->GPIO_HIGH_IE &= ~(1 << pin);
	GPIO->GPIO_FALL_IE &= ~(1 << pin);
	GPIO->GPIO_RISE_IE &= ~(1 << pin);
}

void gpio_rise_interrupt_enable(GPIO_Registers_t *GPIO, unsigned int pin) {
	GPIO->GPIO_RISE_IE |= (1 << pin);
	GPIO->GPIO_HIGH_IE |= (1 << pin);

	// disable all others on that pin:
	//GPIO->GPIO_HIGH_IE &= ~(1 << pin);
	GPIO->GPIO_FALL_IE &= ~(1 << pin);
	GPIO->GPIO_LOW_IE &= ~(1 << pin);
}

void gpio_fall_interrupt_enable(GPIO_Registers_t *GPIO, unsigned int pin) {
	GPIO->GPIO_FALL_IE |= (1 << pin);
	//GPIO->GPIO_LOW_IE |= (1 << pin);

	// disable all others on that pin:
	GPIO->GPIO_HIGH_IE &= ~(1 << pin);
	GPIO->GPIO_RISE_IE &= ~(1 << pin);
	GPIO->GPIO_LOW_IE &= ~(1 << pin);
}


/*
 * Once the interrupt is pending, it will remain set
 * until a 1 is written to the *_ip register at that bit.
 *
 * This function can be used at init time to clear all
 * pending interrupts from GPIO
 */

void gpio_clear_all_pending(GPIO_Registers_t *GPIO){
	GPIO->GPIO_FALL_IP = 0xffffffff;
	GPIO->GPIO_RISE_IP = 0xffffffff;
	GPIO->GPIO_HIGH_IP = 0xffffffff;
	GPIO->GPIO_LOW_IP = 0xffffffff;
}




void _gpio23_handler(){

	//clear GPIO interrupt pending bit 13
	GPIO_REGISTERS_STRUCT_POINTER->GPIO_FALL_IP |= (1 << 23);

	//Toggle pin 22 (LED RED);
	GPIO_REGISTERS_STRUCT_POINTER->GPIO_OUTPUT_VAL ^= (1 << 22);
}


