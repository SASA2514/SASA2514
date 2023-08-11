/*
 * main.c
 *
 *  Created on: 18 Jul 2023
 *      Author: mosta
 */
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#define SET_BIT(SET,BIT_NUMBER)    (SET|=(1<<BIT_NUMBER))//NO SPACE IN DEFINE
#define CLR_BIT(CLR,BIT_NUMBER)    (CLR&=(~(1<<BIT_NUMBER)))
#define RS 1
#define RW 0
#define E  2
#define LCD_CLR LCD_Sendcommand(0b00000001);//FUNCTION
	void LCD_Sendcommand(char command);
	void LCD_SendStr (char *ptr);
	void LCD_SendData(char DATA);
	void SET_COURSER(unsigned char X_POSITION, unsigned char Y_POSITION);
	char My_Name[]="MOSTAFA";
	char COMPANY[]="IMT";
	char SUPERVISOR[]=" MOHAMED YOSRY";
	char FACULTY[]="NDETI";

	int main (void)
	{

		DDRA=0Xff;//PORTA AS OUTPUT
		DDRB=0x07;//111 BINARY PINS 0 1 2 IN PORTB AS OUTPUT
		_delay_ms(50);
		LCD_Sendcommand(0X02);// HOMING
		_delay_ms(30);
		LCD_Sendcommand(0X38);// SET FUNCTION
		_delay_ms(30);
		LCD_Sendcommand(0X0C); // DISPLAY ON BLINK ON
		_delay_ms(30);
		LCD_Sendcommand(0b00000001);// CLEAR
        _delay_ms(5);
        LCD_Sendcommand(0X06);//ENTER MODE
        _delay_ms(15);
        LCD_Sendcommand(0b00000001);//CLEAR
        _delay_ms(50);
        LCD_SendStr(My_Name);
        _delay_ms(500);
        SET_COURSER(1,1);
        LCD_SendStr(FACULTY);
        _delay_ms(500);
        LCD_CLR;
        LCD_SendStr(SUPERVISOR);
        SET_COURSER(1,0);
        _delay_ms(500);
        SET_COURSER(1,1);
        LCD_SendStr(COMPANY);
        _delay_ms(500);
		while(1)
		{

		}
	}

	 void LCD_Sendcommand(char command)
	        {
	        CLR_BIT(PORTB,RS);//RESET RS
	      	CLR_BIT(PORTB,RW);//RESET RW
	        SET_BIT(PORTB,E);//SET E

	        PORTA = command;
	        CLR_BIT(PORTB,E);//RESET E
	        _delay_ms(5);
	         SET_BIT(PORTB,E);//SET E
	        _delay_ms(5);
	        CLR_BIT(PORTB,E);//RESET E
	        }
	 void LCD_SendData(char DATA)
	 	        {
	 	        SET_BIT(PORTB,RS);//RESET RS
	 	      	CLR_BIT(PORTB,RW);//RESET RW
	 	        SET_BIT(PORTB,E);//SET E

	 	        PORTA = DATA ;
	 	        CLR_BIT(PORTB,E);//RESET E
	 	        _delay_ms(5);
	 	         SET_BIT(PORTB,E);//SET E
	 	        _delay_ms(5);
	 	        //CLR_BIT(PORTB,E);//RESET E
	 	        }
	 void LCD_SendStr (char *ptr)

	 {
		 int counter = 0 ;
		 while(1)
		 {
			 if(ptr[counter]=='\0')
			 {
				 break;
			 }
			 LCD_SendData(ptr[counter]);
			 counter++;
		 }
		 return;
	 }
	 void SET_COURSER(unsigned char X_POSITION, unsigned char Y_POSITION)
		{
			int add ;
			if (X_POSITION==0)
			{
				add = 0x80;
			}
			else if (X_POSITION==1)
			{
				add = 0xC0;
			}
			if(Y_POSITION<16)
			{
				add += Y_POSITION;
			}
			LCD_Sendcommand(add);
		}

