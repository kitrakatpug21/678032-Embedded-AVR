/*
 * SPI-Master (Switch Controlled).c
 *
 * Created: 22-08-2022 12:54:04 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	DDRB = 0b10100000;
	SPCR = 0b01010000;
	DDRA = 0b00000011;
	DDRD = 0b00000011;
	volatile uint8_t temp;
	PORTA = 0b00000011;
	PORTD = 0b00000011;
	uint8_t data = 0;
	while (1)
	{
		if (PINC & 0b00000001)
		{
			PORTA = 0b00000010;// SLAVE-1 is ON SLAVE-2 is OFF
			PORTD = 0b00000011;// SLAVE-3 is OFF SLAVE-4 is OFF
		}
		else if (PINC & 0b00000010)
		{
			PORTA = 0b00000001;// SLAVE-1 is OFF SLAVE-2 is ON
			PORTD = 0b00000011;// SLAVE-3 is OFF SLAVE-4 is OFF
		}
		else if (PINC & 0b00000100)
		{
			PORTA = 0b00000011;// SLAVE-1 is OFF SLAVE-2 is OFF
			PORTD = 0b00000010;// SLAVE-3 is ON SLAVE-4 is OFF
		}
		else if (PINC & 0b00001000)
		{
			PORTA = 0b00000011;// SLAVE-1 is OFF SLAVE-2 is OFF
			PORTD = 0b00000001;// SLAVE-3 is OFF SLAVE-4 is ON
		}
		SPDR = data;
		while ((SPSR & 0b10000000) == 0)
		{
				// wait here till the SPIF bit == 1
		}
			// now clear the status bits
			temp = SPSR;// first read the SPSR bit
			temp = SPDR;// then read the SPDR register
			_delay_ms(1000);
		data = data + 1;
	}
}


