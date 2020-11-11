/*
 * 201111.c
 *
 * Created: 2020-11-11 오전 10:46:12
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/delay.h>
#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;
	DDRF = 0x00;
	
	ADMUX = 0x40;
	ADCSRA = 0x87;
	
	PORTA = 0x01;
	_delay_ms(3000);
    while (1) 
    {
		ADCSRA |= 0x40;
		while((ADCSRA & 0x10) != 0x10);

		if ((unsigned short)(ADCL | (ADCH << 8)) < 100) PORTA = 0x02;
		else PORTA = 0x04;

		
    }
}

