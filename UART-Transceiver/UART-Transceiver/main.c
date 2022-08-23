/*
 * UART-Transceiver.c
 *
 * Created: 23-08-2022 01:20:31 PM
 * Author : kartik.iot
 */ 

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

void UART_Init()
{
	// Baud Rate (at 9600 for 8MHz Clock) Setup in UBRR
	DDRD = 0b00000010;
	UBRRH = 0;
	UBRRL = 51;
	UCSRB = 0b00011000; // RXEN TXEN
	UCSRC = 0b10100110; // URSEL Asynch Par-Ev St-1 Data-8
}

void UART_Transmit(uint8_t data)
{
	while ((UCSRA & 0b00100000)==0)
	{
		// we wait till the Transmission Buffer is not empty
	}
	// once it is empty, Load a new Data in it
	UDR = data;
}

uint8_t UART_Receive()
{
	while ((UCSRA & 0b10000000)==0)
	{
		// we wait till the Receiving Buffer is not full
	}
	// once it is full, Upload the same data on PORTC
	return UDR;
}

int main(void)
{
    UART_Init();
	while (1) 
    {
		UART_Transmit(UART_Receive()); 
    }
}

