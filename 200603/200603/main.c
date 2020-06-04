/*
 * 200603.c
 *
 * Created: 2020-06-03 오전 9:58:59
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA = 0xFF;
	DDRE = 0x00;
	PORTA = 0x00;
	signed char dir = -1;
    /* Replace with your application code */
    while (1) 
    {
		PORTA = PORTA << dir;
		PORTA = PORTA >> (!dir);
		
		if(PORTA == 0x00)
		{
			PORTA = (0x01 ^ dir) << 7;
			if(dir == 1) PORTA = 0x01;
		}
		
		if(!(PINE & 0x10)) dir = 1;
		if(!(PINE & 0x20)) dir = 0;
		_delay_ms(500);
    }
}

