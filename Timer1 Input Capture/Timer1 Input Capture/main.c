/*
 * Timer1 Input Capture.c
 *
 * Created: 16-08-2022 12:10:41 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <stdio.h>
#include <stdlib.h>

#include <util/delay.h>

void LCD_Config(uint8_t cmd)
{
	// 1. Set RS Pin to 0
	PORTC = 0b00000000;
	// 2. Load the Data on PORTD
	PORTB = cmd;
	// 3. Create a Positive Edge Signal On EN Pin
	PORTC = 0b00000010;
	_delay_ms(10);
	PORTC = 0b00000000;
	_delay_ms(10);
}
void LCD_Alphabet(char ch)
{
	// 1. Set RS Pin to 1
	PORTC = 0b00000001;
	// 2. Load the Data on PORTD
	PORTB = ch;
	// 3. Create a Positive Edge Signal On EN Pin
	PORTC = 0b00000011;
	_delay_ms(10);
	PORTC = 0b00000001;
	_delay_ms(10);
}

void LCD_Start()
{
	_delay_ms(300);// LCD Require 300ms to POWER ON
	LCD_Config(0x38);
	/*
	0x38 ->	LCD will perform operation as 8-bit 2 row 16 character mode
	0x30 -> LCD will perform operation as 8-bit 1 row 16 character mode
	*/
	LCD_Config(0x06);
	/*
	0x06 ->	LCD will write characters from LEFT to RIGHT
	0x04 -> LCD will write characters from RIGHT to LEFT
	*/
	LCD_Config(0x0C);
	/*
	0x0C ->	LCD will have No Cursor
	0x0E -> LCD will have _ cursor
	0x0F -> LCD will have blinky | cursor
	*/
	LCD_Config(0x01);	// to clear any garbage values on LCD Display
	_delay_ms(10);
}

void LCD_print(char *str)
{
	while (*str != '\0')
	{
		LCD_Alphabet(*str);
		str++;
	}
}

int main(void)
{
    DDRC = 0b00000011;	//  EN RS
    DDRB = 0b11111111;	// D7..D0
    LCD_Start();
	TCCR1A = 0;// no need to generate any output
	int a,b,c, duty_cycle, frequency;
	while (1) 
    {
		TCCR1B = 0b01000001; // capture rising edge at DIv by 1 Prescale
		TIFR = 0b00100000;// clear the ICF1 Flag
		while ((TIFR & 0b00100000)==0)
		{
			// until the rising edge is captured, wait here
		}
		// once rising edge is captured, copy the ICR value in a variable
		a = ICR1;
		TCCR1B = 0b00000001; // capture falling edge at DIv by 1 Prescale
		TIFR = 0b00100000;// clear the ICF1 Flag
		while ((TIFR & 0b00100000)==0)
		{
			// until the rising edge is captured, wait here
		}
		// once falling edge is captured, copy the ICR value in a variable
		b = ICR1;
		TCCR1B = 0b01000001; // capture rising edge at DIv by 1 Prescale
		TIFR = 0b00100000;// clear the ICF1 Flag
		while ((TIFR & 0b00100000)==0)
		{
			// until the rising edge is captured, wait here
		}
		// once rising edge is captured, copy the ICR value in a variable
		c = ICR1;
		TCCR1B = 0;// terminate the timer
		char duty[16], freq[16];
		duty_cycle = (((b-a)*100) / (c-a));
		frequency = F_CPU/(c-a);
		sprintf(freq, "Freq: %d Hz ",frequency);
		sprintf(duty, "Duty: %d %%",duty_cycle);
		LCD_Config(0x80);LCD_print(duty);
		LCD_Config(0xC0);LCD_print(freq);
    }
}

