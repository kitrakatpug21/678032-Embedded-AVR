/*
 * Multiple ADC Interface.c
 *
 * Created: 02-08-2022 12:23:46 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void ADC_Init(uint8_t channel)
{
	ADMUX = 0b01000000;
	ADCSRA = 0b10000110;// basic setup
	ADMUX = ADMUX | channel;
}
// uint16_t ADC_Result()
void ADC_Result()
{
	ADCSRA = ADCSRA | (0b01000000);// ADD Start bit on existing ADCSRA Value
	while ((ADCSRA & (1<<4))==0)
	{
		//wait till conversion completes
	}
	PORTC = ADCL;//comment
	PORTD = ADCH;//comment
	// return ADC;
}

int main(void)
{
	DDRC = 0b11111111;
	DDRD = 0b00000011;
	///int reading;
	while (1)
	{
		ADC_Init(0);
		ADC_Result();
		// reading = ADC_Result();
		_delay_ms(1000);
		ADC_Init(4);
		ADC_Result();
		_delay_ms(1000);
		ADC_Init(7);
		ADC_Result();
		_delay_ms(1000);
	}	
}
