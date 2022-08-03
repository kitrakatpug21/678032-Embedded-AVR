/*
 * Temperature Sensor Interface.c
 *			
 * Created: 01-08-2022 01:22:00 PM
 * Author : kartik.iot
 */  

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	ADMUX = 0b01000011;
	ADCSRA = 0b10000110;
	DDRC = 0b00000111;
	while (1)
	{
		ADCSRA = 0b11000110;
		while ((ADCSRA & (1<<4))==0)
		{
			//wait till conversion completes
		}
		if (ADC >= 62)
		{
			//if temp > 30
			//Fan1 + Fan2 + Compressor
			PORTC = 0b00000111;
		}
		else if (ADC < 62 && ADC >= 52)
		{
			//if 30 > temp > 25
			//Fan1 + compressor
			PORTC = 0b00000101;
		}
		else if (ADC < 52 && ADC >= 41)
		{
			//if 25 > temp 20
			//Fan1 + Fan2
			PORTC = 0b00000110;
		}
		else if (ADC < 41 && ADC >= 31)
		{
			//if 20 > temp 15
			//Fan1
			PORTC = 0b00000100;
		}
		else
		{
			// everything off otherwise
			PORTC = 0b00000000;
		}
		_delay_ms(100);
	}
}

