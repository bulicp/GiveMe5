#ifndef CGPIO_H_
#define CGPIO_H_


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




#endif
