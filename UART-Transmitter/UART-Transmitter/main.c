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
	UCSRB = 0b00001000; // TXEN 
	UCSRC = 0b10100110; // URSEL Asynch Par-Ev St-1 Data-8
	char array[8] = "Gopal\r\n";
	while (1) 
    {
		for (int i=0; i<8; i=i+1)
		{
			while ((UCSRA & 0b00100000)==0)
			{
				// we wait till the Transmission Buffer is not empty
			}
			// once it is empty, Load a new Data in it
			UDR = array[i];
			_delay_ms(100);			
		}
		 
    }
}

