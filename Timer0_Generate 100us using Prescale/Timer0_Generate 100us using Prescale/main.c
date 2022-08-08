/*
 * Timer0_Generate 100us using Prescale.c
 *
 * Created: 08-08-2022 01:01:22 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL

int main(void)
{
    TCCR0 = 0b00011010;// CTC Mode (Toggle) Prescale by 8
	DDRB = 0b00001000;
	TCNT0 = 0;
	OCR0 = 100;
	while (1) 
    {
		while ((TIFR & 0b00000010)==0)
		{
			// wait here till TCNT is not equal to OCR value
		}
		// as soon as time they match, Toggle the OC0 Pin
    }
}


