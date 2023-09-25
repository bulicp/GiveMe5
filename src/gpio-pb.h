#ifndef GPIO_PB_H_
#define GPIO_PB_H_


#define GPIO_BASEADDR     0x10012000

typedef struct
{
	volatile int GPIO_INPUT_VAL;
	volatile int GPIO_INPUT_EN;
	volatile int GPIO_OUTPUT_EN;
	volatile int GPIO_OUTPUT_VAL;
	volatile int GPIO_PUE;
	volatile int GPIO_DS;
	volatile int GPIO_RISE_IE;
	volatile int GPIO_RISE_IP;
	volatile int GPIO_FALL_IE;
	volatile int GPIO_FALL_IP;
	volatile int GPIO_HIGH_IE;
	volatile int GPIO_HIGH_IP;
	volatile int GPIO_LOW_IE;
	volatile int GPIO_LOW_IP;
	volatile int GPIO_IOF_EN;
	volatile int GPIO_IOF_SEL;
	volatile int GPIO_OUT_XOR;
}GPIO_Registers_t;

#define GPIO_REGISTERS_STRUCT_POINTER ((GPIO_Registers_t *)GPIO_BASEADDR)


void gpio_input_enable(GPIO_Registers_t *GPIO, unsigned int pin);
void gpio_output_enable(GPIO_Registers_t *GPIO, unsigned int pin);
void gpio_toggle(GPIO_Registers_t *GPIO, unsigned int pin);
void gpio_pullup_enable(GPIO_Registers_t *GPIO, unsigned int pin);
void gpio_high_interrupt_enable(GPIO_Registers_t *GPIO, unsigned int pin);
void gpio_low_interrupt_enable(GPIO_Registers_t *GPIO, unsigned int pin);
void gpio_rise_interrupt_enable(GPIO_Registers_t *GPIO, unsigned int pin);
void gpio_fall_interrupt_enable(GPIO_Registers_t *GPIO, unsigned int pin);
void gpio_clear_all_pending(GPIO_Registers_t *GPIO);


/* GPIO assembler functions */
void gpio_output_en(int pin);
void gpio_input_en(int pin);
int gpio_get_pin_val(int pin);
void gpio_set_pin(int pin);
void gpio_toggle_pin(int pin);
void gpio_clear_pin(int pin);




#endif
