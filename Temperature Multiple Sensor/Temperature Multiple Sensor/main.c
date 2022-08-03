/*
 * Temperature Multiple Sensor.c
 *
 * Created: 02-08-2022 01:00:35 PM
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
uint16_t ADC_Result()
{
	ADCSRA = ADCSRA | (0b01000000);// ADD Start bit on existing ADCSRA Value
	while ((ADCSRA & (1<<4))==0)
	{
		//wait till conversion completes
	}
	//PORTC = ADCL;//comment
	//PORTD = ADCH;//comment
	return ADC;
}

int main(void)
{
	DDRC = 0b00000111;// AC-1
	DDRD = 0b00000111;// AC-2
	int reading;
	while (1)
	{
		ADC_Init(0);
		//ADC_Result();
		reading = ADC_Result();
		if (reading >= 62)
		{
			//if temp > 30
			//Fan1 + Fan2 + Compressor
			PORTC = 0b00000111;
		}
		else if (reading < 62 && reading >= 52)
		{
			//if 30 > temp > 25
			//Fan1 + compressor
			PORTC = 0b00000101;
		}
		else if (reading < 52 && reading >= 41)
		{
			//if 25 > temp 20
			//Fan1 + Fan2
			PORTC = 0b00000110;
		}
		else if (reading < 41 && reading >= 31)
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
		ADC_Init(1);
		reading = ADC_Result();
		if (reading >= 62)
		{
			//if temp > 30
			//Fan1 + Fan2 + Compressor
			PORTD = 0b00000111;
		}
		else if (reading < 62 && reading >= 52)
		{
			//if 30 > temp > 25
			//Fan1 + compressor
			PORTD = 0b00000101;
		}
		else if (reading < 52 && reading >= 41)
		{
			//if 25 > temp 20
			//Fan1 + Fan2
			PORTD = 0b00000110;
		}
		else if (reading < 41 && reading >= 31)
		{
			//if 20 > temp 15
			//Fan1
			PORTD = 0b00000100;
		}
		else
		{
			// everything off otherwise
			PORTD = 0b00000000;
		}
		_delay_ms(100);
	}
}
