/*
 * UART-Receiver.c
 *
 * Created: 23-08-2022 01:10:33 PM
 * Author : kartik.iot
 */ 
/*
 * UART-Transmitter.c
 *
 * Created: 23-08-2022 12:54:37 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
    // Baud Rate (at 9600 for 8MHz Clock) Setup in UBRR
	DDRD = 0b00000010;
	UBRRH = 0;
	UBRRL = 51;
	UCSRB = 0b00010000; // RXEN 
	UCSRC = 0b10100110; // URSEL Asynch Par-Ev St-1 Data-8
	DDRC = 0b11111111;
	while (1) 
    {
		while ((UCSRA & 0b10000000)==0)
		{
			// we wait till the Receiving Buffer is not full
		}
		// once it is full, Upload the same data on PORTC
		PORTC = UDR;		 
    }
}

