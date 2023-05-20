#include "bsp.h"

#define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028)) 
#define UART0_RIS_R             (*((volatile unsigned long *)0x4000C03C))
#define UART0_MIS_R             (*((volatile unsigned long *)0x4000C040))
#define UART0_ICR_R             (*((volatile unsigned long *)0x4000C044)) 
#define SYSCTL_RCGCUART_R       (*((volatile unsigned long *)0x400FE618))
#define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030)) 
#define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C02C)) 
#define UART0_CC_R              (*((volatile unsigned long *)0x4000CFC8)) 



void UART_init(){
	SYSCTL->RCGCUART |= 0x01; 									/* enable clock to UART0 */
	for(volatile int i=0; i<2; i++);
	UART0->CTL = 0;         										/* UART1 module disbable */
	/* 16MHz/16=1MHz, 1MHz/9600=104 baud rate 
	0.166 x 64 + 0.5 = 11 */
	UART0->IBRD = 104;      										/* for 9600 baud rate, integer = 104 */
	UART0->FBRD = 11;       										/* for 9600 baud rate, fractional = 11*/
	UART0->CC = 0;          										/*select system clock*/
	UART0->LCRH = 0x60;     										/* data lenght 8-bit, not parity bit, no FIFO */
	UART0->CTL = 0x301;     										/* Enable UART5 module, Rx and Tx */
	UART0->ICR |= (1<<4);												/* Clear interrupt*/
	UART0->IM  |= (1<<4);                       /* Interrupt Mask */
	NVIC_SetPriority(UART0_IRQn,5);             /* Change UART Priority */
	NVIC_EnableIRQ(UART0_IRQn);									/* Enable UART0 interrupt */
}

void uart0_putchar(char data){
	while ((UART0->FR & 0x20) != 0);			 		 	/* wait until Tx buffer not full */
	UART0->DR = data; 													/* before giving it another byte */
}

char uart0_Receivechar(void){
    char data;
	  while((UART0->FR & (1<<4)) != 0); 				/* wait until Rx buffer is not full */
    data = UART0->DR ;  											/* before giving it another byte */
    return (unsigned char) data; 
}

void PORTA_init(){
	SYSCTL->RCGCGPIO |= 0x01; 									/* enable clock to PORTA */
	for(volatile int i=0; i<2; i++);
	GPIOA->DEN = GPIOA->AFSEL = 0x03; 					/* set PA0 and PA1 as digital */ /* Use PA0,PA1 alternate function */
	GPIOA->PCTL = 0x00000011;										/* configure PA0 and PA1 for UART */
}
	
void PORTF_init(){
	SYSCTL->RCGCGPIO |= 0x20;
	for(volatile int i=0; i<2; i++);
	GPIOF->DIR = GPIOF->DEN |= RED_LED;					/* direction is out in pin 1 in port F && digital I/O is enabled */
}


