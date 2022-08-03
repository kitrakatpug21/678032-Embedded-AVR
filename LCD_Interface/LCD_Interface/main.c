/*
 * LCD_Interface.c
 *
 * Created: 03-08-2022 12:31:28 PM
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
	DDRD = 0b11111111;	// D7..D0
	LCD_Start();
    while (1) 
    {
		LCD_Config(0x8F);LCD_Config(0x04);
		LCD_print("NIMANSHU");
		//LCD_Alphabet('R');LCD_Alphabet('A');LCD_Alphabet('H');LCD_Alphabet('U');LCD_Alphabet('L');
		_delay_ms(1000);
		LCD_Config(0x01); _delay_ms(10);
		LCD_Config(0xCF);LCD_Config(0x04);
		//LCD_Alphabet('P');LCD_Alphabet('A');LCD_Alphabet('W');LCD_Alphabet('A');LCD_Alphabet('N');
		LCD_print("LAPOG");
		_delay_ms(1000);
		LCD_Config(0x01); _delay_ms(10);
		LCD_Config(0x88);LCD_Config(0x04);
		LCD_print("NUJRA");
		//LCD_Alphabet('R');LCD_Alphabet('A');LCD_Alphabet('H');LCD_Alphabet('U');LCD_Alphabet('L');
		_delay_ms(1000);
		LCD_Config(0x01); _delay_ms(10);
		LCD_Config(0xC8);LCD_Config(0x04);
		//LCD_Alphabet('P');LCD_Alphabet('A');LCD_Alphabet('W');LCD_Alphabet('A');LCD_Alphabet('N');
		LCD_print("KUNAL");
		_delay_ms(1000);
		LCD_Config(0x01); _delay_ms(10);
    }
}

