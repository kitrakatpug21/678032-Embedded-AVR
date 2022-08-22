/*
 * EEPROM Interfacing.c
 *
 * Created: 17-08-2022 01:00:38 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void EEPROM_Write(uint8_t Addr, uint8_t Data)
{
	/* Wait for completion of previous write */
	while (EECR & 0b00000010);// EEWE is not 0
	/* Set up address and data registers */
	EEAR = Addr;
	EEDR = Data;
	/* Write logical one to EEMWE */
	EECR = EECR | 0b00000100;
	/* Start EEPROM write by setting EEWE */
	EECR = EECR | 0b00000010;
}
uint8_t EEPROM_Read(uint8_t Addr)
{
	/* Wait for completion of previous write */
	while (EECR & 0b00000010);// EEWE is not 0
	/* Set up address and data registers */
	EEAR = Addr;
	/* Start EEPROM read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

int main(void)
{
	DDRA = 0b00000000; // ADDRESS
	DDRB = 0b00000000; // DATA (Write)
	DDRC = 0b11111111; // DATA (Read)
	DDRD = 0b00000000; // PD6 -> Read		PD2 -> Write
	while (1) 
    {
		if (PIND & 0b00000100)
		{
			// PD2 is HIGH => WRITE INTO EEPROM
			EEPROM_Write(PINA,PINB);
		}
		if (PIND & 0b01000000)
		{
			// PD6 is HIGH => READ FROM EEPROM
			PORTC = EEPROM_Read(PINA);
		}
    }
}

