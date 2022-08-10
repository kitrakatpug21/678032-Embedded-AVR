/*
 * Timer0 CTC (Frequency Generator) Mode.c
 *
 * Created: 09-08-2022 12:07:48 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL

int main(void)
{
	TCCR0 = 0b00011001;// CTC Mode (Toggle) Prescale by 1
	DDRB = 0b00001000;
	TCNT0 = 0;
	OCR0 = 1;
	while (1)
	{
		if (PINA & 0b00000001)
		{
			TCCR0 = 0b00011001;// CTC Mode (Toggle) Prescale by 1
			TCNT0 = 0;
			OCR0 = 50;
		}
		else if (PINA & 0b00000010)
		{
			TCCR0 = 0b00011001;// CTC Mode (Toggle) Prescale by 1
			TCNT0 = 0;
			OCR0 = 200;
		}
		else if (PINA & 0b00000100)
		{
			TCCR0 = 0b00011010;// CTC Mode (Toggle) Prescale by 8
			TCNT0 = 0;
			OCR0 = 100;
		}
		else if (PINA & 0b00001000)
		{
			TCCR0 = 0b00011011;// CTC Mode (Toggle) Prescale by 16
			TCNT0 = 0;
			OCR0 = 100;
		}
		
		while ((TIFR & 0b00000010)==0)
		{
			// wait here till TCNT is not equal to OCR value
		}
		// as soon as time they match, Toggle the OC0 Pin
	}
}



