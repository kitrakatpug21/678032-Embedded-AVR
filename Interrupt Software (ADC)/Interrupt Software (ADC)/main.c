/*
 * Interrupt Software (ADC).c
 *
 * Created: 04-08-2022 01:00:27 PM
 * Author : kartik.iot
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

uint16_t Data;
ISR (ADC_vect)
{
	Data = ADC;
	PORTD = 0b00000101;
	for (long delay = 0; delay <= 40000; delay = delay + 1);
	PORTD = 0b00000000;
	for (long delay = 0; delay <= 40000; delay = delay + 1);
	PORTD = 0b00001010;
	for (long delay = 0; delay <= 40000; delay = delay + 1);
	PORTD = 0b00000000;
	for (long delay = 0; delay <= 40000; delay = delay + 1);
}

int main(void)
{
	ADMUX = 0b01000011;
	ADCSRA = 0b10001110;
	DDRC = 0b00000111;
	DDRD = 0b00001111;
	sei();
	while (1)
	{
		ADCSRA = 0b11001110;
// 		while ((ADCSRA & (1<<4))==0)
// 		{
// 			//wait till conversion completes
// 		}
		if (Data >= 62)
		{
			//if temp > 30
			//Fan1 + Fan2 + Compressor
			PORTC = 0b00000111;
		}
		else if (Data < 62 && Data >= 52)
		{
			//if 30 > temp > 25
			//Fan1 + compressor
			PORTC = 0b00000101;
		}
		else if (Data < 52 && Data >= 41)
		{
			//if 25 > temp 20
			//Fan1 + Fan2
			PORTC = 0b00000110;
		}
		else if (Data < 41 && Data >= 31)
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