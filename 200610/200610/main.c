/*
 * 200610.c
 *
 * Created: 2020-06-10 오전 8:54:33
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
		PORTA = ~PORTA;
		_delay_ms(500);
	    if(PINE == 0xCF)
		{
			PORTA = 0xAA;
		}
		else if(~PINE & 0x20)
		{
			PORTA = 0x33;
		}
		else if(~PINE & 0x10)
		{
			PORTA = 0x0F;
		}
		else
		{
			PORTA = 0xFF;
		}
		_delay_ms(500);
    }
}

