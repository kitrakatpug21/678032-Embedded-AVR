/*
 * Timer with LCD.c
 *
 * Created: 09-08-2022 12:46:38 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void LCD_Config(uint8_t cmd)
{
	// 1. Set RS Pin to 0
	PORTC = 0b00000000;
	// 2. Load the Data on PORTD
	PORTD = cmd;
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
	PORTD = ch;
	// 3. Create a Positive Edge Signal On EN Pin
	PORTC = 0b00000011;
	_delay_ms(10);
	PORTC = 0b00000001;
	_delay_ms(10);
}

void LCD_Start()
{
	DDRC = 0b00000011;
	DDRD = 0b11111111;
	//_delay_ms(300);// LCD Require 300ms to POWER ON
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
	//TCCR0 = 0b00011001;// CTC Mode (Toggle) Prescale by 1
	DDRB = 0b00001000;
	//TCNT0 = 0;
	//OCR0 = 1;
	LCD_Start();
	LCD_Config(0x80);
	LCD_print("HELLO");
	while (1)
	{
		if (PINA & 0b00000001)
		{
			TCCR0 = 0;// turn timer off
			LCD_Config(0x80);
			LCD_print("Frequency: 10us  ");
			TCCR0 = 0b00011001;// CTC Mode (Toggle) Prescale by 1
			TCNT0 = 0;
			OCR0 = 50;
		}
		else if (PINA & 0b00000010)
		{
			TCCR0 = 0;// turn timer off
			LCD_Config(0x80);
			LCD_print("Frequency: 40us  ");
			TCCR0 = 0b00011001;// CTC Mode (Toggle) Prescale by 1
			TCNT0 = 0;
			OCR0 = 200;
		}
		else if (PINA & 0b00000100)
		{
			TCCR0 = 0;// turn timer off
			LCD_Config(0x80);
			LCD_print("Frequency: 160us");
			TCCR0 = 0b00011010;// CTC Mode (Toggle) Prescale by 8
			TCNT0 = 0;
			OCR0 = 100;
		}
		else if (PINA & 0b00001000)
		{
			TCCR0 = 0;// turn timer off
			LCD_Config(0x80);
			LCD_print("Frequency: 320us");
			TCCR0 = 0b00011011;// CTC Mode (Toggle) Prescale by 16
			TCNT0 = 0;
			OCR0 = 100;
		}
		if (TCCR0 != 0)
		{
			while ((TIFR & 0b00000010)==0)
			{
				// wait here till TCNT is not equal to OCR value
			}
		}
		// as soon as time they match, Toggle the OC0 Pin
	}
}



