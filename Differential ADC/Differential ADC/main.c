/*
 * Differential ADC.c
 *
 * Created: 02-08-2022 01:18:05 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void ADC_Result()
{
	ADCSRA = ADCSRA | 0b01000000;// start of conv
	while((ADCSRA & (1<<4))==0)
	{
		// until the ADIF is 1, wait here
	}
	PORTC = ADCL;
	PORTD = ADCH;
}

int main(void)
{
	ADMUX = 0b01010000;// ADC0-> Vin	ADC1-> Vdiff
	ADCSRA = 0b10000110;
	DDRC = 0b11111111;
	DDRD = 0b00000011;
	while (1)
	{
		ADC_Result();
		_delay_ms(100);
	}
}

