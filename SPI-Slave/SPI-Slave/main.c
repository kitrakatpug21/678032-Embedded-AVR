/*
 * SPI-Slave.c
 *
 * Created: 22-08-2022 12:43:09 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	DDRB = 0b01000000;
    SPCR = 0b01000000;
	DDRD = 0b11111111;
	volatile uint8_t temp;
	while (1) 
    {
		while ((SPSR & 0b10000000) == 0)
		{
			// wait here till the SPIF bit == 1
		}
		PORTD = SPDR;
		// now clear the status bits
		temp = SPSR;// first read the SPSR bit
		temp = SPDR;// then read the SPDR register
    }
}

