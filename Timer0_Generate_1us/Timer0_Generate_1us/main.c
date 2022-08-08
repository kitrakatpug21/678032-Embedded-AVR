/*
 * Timer0_Generate_1us.c
 *
 * Created: 08-08-2022 12:27:43 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL

int main(void)
{
    TCCR0 = 0b00000001;
	DDRA = 0b00000001;
	PORTA = 0b00000000;
	while (1) 
    {
		TCNT0 = 247;
		while ((TIFR & 0b00000001)==0)
		{
			// wait here till timer have not reached TOP (255)
		}
		// as soon as time reach TOP, Toggle the PORTA pin 0
		PORTA = ~PORTA;
    }
}

