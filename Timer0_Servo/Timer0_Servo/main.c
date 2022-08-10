/*
 * Timer0_Servo.c
 *
 * Created: 10-08-2022 12:48:06 PM
 * Author : kartik.iot
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

uint16_t getResult()
{
	ADCSRA = 0b11000110;// start of conv
	while((ADCSRA & (1<<4))==0)
	{
		// until the ADIF is 1, wait here
	}
	return ADC;
}

int main(void)
{
	ADMUX = 0b01000000;// ADC channel 0 
	ADCSRA = 0b10000110;
	TCCR0 = 0b01101011;// PWM Mode (Clear OC0 on compare match, set OC0 at BOTTOM) Prescale by 64
	DDRB = 0b00001000;
	TCNT0 = 0;
	OCR0 = 0;
	while (1)
	{
		OCR0 = getResult();
		while ((TIFR & 0b00000001)==0)
		{
			// wait here till TOP is reached
		}
	}
}