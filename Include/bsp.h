#ifndef BSP_H
#define BSP_H

#include "TM4C123.h"
#include <string.h>
#include <math.h>  

#define RED_LED 							((unsigned int)(1<<1))
#define NEWLINE 0x0A
#define CARRIAGE_RETURN 0x0D

void UART_init();
void PORTA_init();
char uart0_Receivechar(void);
void uart0_putchar(char data);

void PORTF_init();

#endif
