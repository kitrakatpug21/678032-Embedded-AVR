/*
 * Timer0 PWM (Duty Cycle) Mode.c
 *
 * Created: 10-08-2022 11:59:57 AM
 * Author : kartik.iot
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void)
{
	//TCCR0 = 0b01111101;// PWM Mode (Set OC0 on compare match, clear OC0 at BOTTOM) Prescale by 1024
	TCCR0 = 0b01101101;// PWM Mode (Clear OC0 on compare match, set OC0 at BOTTOM) Prescale by 1024
	DDRB = 0b00001000;
	TCNT0 = 0;
	OCR0 = 0;
	while (1)
	{
		for (int i = 0; i <= 255; i = i+1)
		{
			OCR0 = i;
			while ((TIFR & 0b00000001)==0)
			{
				// wait here till TOP is reached
			}
			_delay_ms(100);
		}
		for (int i = 255; i >= 0; i = i-1)
		{
			OCR0 = i;
			while ((TIFR & 0b00000001)==0)
			{
				// wait here till TOP is reached
			}
			_delay_ms(100);
		}
		/*for (int i = 0; i <= 255; i = i+1)
		{
			OCR0 = i;	
			while ((TIFR & 0b00000001)==0)
			{
				// wait here till TOP is reached
			}
			_delay_ms(10);
		}*/
	}
}