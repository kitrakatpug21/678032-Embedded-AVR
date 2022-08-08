/*
 * Interrupts.c
 *
 * Created: 04-08-2022 12:21:25 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (INT1_vect)
{
	PORTA = ~PORTA;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
// 	PORTA = 0b00000010;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
// 	PORTA = 0b00000100;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
// 	PORTA = 0b00001000;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
// 	PORTA = 0b00000000;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
// 	PORTA = 0b00001000;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
// 	PORTA = 0b00000100;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
// 	PORTA = 0b00000010;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
// 	PORTA = 0b00000001;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
// 	PORTA = 0b00000000;
// 	for (long delay = 0; delay <= 50000; delay = delay + 1);
	
}


uint8_t segment[10] = {0b00111111,// digit 0
	0b00000110,// digit 1
	0b01011011,// digit 2
	0b01001111,// digit 3
	0b01100110,// digit 4
	0b01101101,// digit 5
	0b01111101,// digit 6
	0b00000111,// digit 7
	0b01111111,// digit 8
	0b01101111};// digit 9

int main(void)
{
	// sevenSeg  .gfedcba
	DDRA = 0b00001111;
	DDRC = 0b01111111;
	GICR = GICR | (0b10000000);		// Enable only INT1
	MCUCR = MCUCR | (0b00001100);	// Setup INT1 to interrupt at any logic change
	sei();
	while (1)
	{
		for (int ones = 0; ones <= 9; ones = ones + 1)
		{
			PORTC = segment[ones];
			_delay_ms(500);
		}
	}
}

