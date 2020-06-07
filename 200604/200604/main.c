/*
 * 200604.c
 *
 * Created: 2020-06-04 오전 9:38:28
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
    unsigned char dir = 0;
	
    while (1)
    {
		if(dir & 0x10)
		{
			PORTA = PORTA & 0x40 ? 0x00 : ((PORTA << 2) | 0x01);	
		}
		if(dir & 0x20)
		{
			PORTA = PORTA & 0x02 ? 0x00 : ((PORTA >> 2) | 0x80);
		}
	    if(~PINE & 0x30)
		{
			dir = ~PINE;
			PORTA = 0x00;
		}
		_delay_ms(500);
    }
}

