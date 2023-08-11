/*
 * main.c
 *
 *  Created on: 25 Jul 2023
 *      Author: mosta
 */
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#define SET_BIT(SET,BIT_NUMBER)    (SET|=(1<<BIT_NUMBER))
#define CLR_BIT(CLR,BIT_NUMBER)    (CLR&=(~(1<<BIT_NUMBER)))
#define GET_BIT(GET,BIT_NUMBER)    (GET>>BIT_NUMBER)&0x01)
unsigned char UART_GETChar(void);
void UART_SendChar(char data);
int main(void)
{
	UCSRB = 0b00011000;//
	UCSRC = 0b10000110;
	UBRRL = 51;
	UBRRH=0;
	UCSRB=0x148;
	UCSRC=0x86;

	while(1)
	{
		UART_SendChar('M');
		_delay_ms(10);
	}

}

void UART_SendChar(char data)
{
	while(! (UCSRA & (1<<UDRE)));
	UDR =data;

}

unsigned char UART_GETChar(void){

	unsigned char Result;
	while((UCSRA&0x80)==0x00);
	Result = UDR;
}
