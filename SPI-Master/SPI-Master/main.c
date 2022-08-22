/*
 * SPI-Master.c
 *
 * Created: 22-08-2022 12:30:45 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	DDRB = 0b10100000;
    SPCR = 0b01010000;
	volatile uint8_t temp;
	while (1) 
    {
		for (uint8_t data = 0; data < 255; data = data + 1)
		{
			SPDR = data;
			while ((SPSR & 0b10000000) == 0)
			{
				// wait here till the SPIF bit == 1
			}
			// now clear the status bits
			temp = SPSR;// first read the SPSR bit
			temp = SPDR;// then read the SPDR register
			_delay_ms(1000);
		}
    }
}

