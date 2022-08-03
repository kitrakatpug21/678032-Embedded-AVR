/*
 * ADC.c
 *
 * Created: 01-08-2022 12:20:45 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	ADMUX = 0b01000011;
	ADCSRA = 0b10000110;
	DDRC = 0b11111111;
	DDRD = 0b00000011;
    while (1) 
    {
		ADCSRA = 0b11000110;// start of conv
		while((ADCSRA & (1<<4))==0)
		{
			// until the ADIF is 1, wait here
		}
		PORTC = ADCL;
		PORTD = ADCH;
		_delay_ms(100);
    }
}

