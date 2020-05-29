/*
 * 200527.c
 *
 * Created: 2020-05-27 오전 11:32:59
 * Author : user
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void print_FND(unsigned short num);

int main(void)
{
    /* Replace with your application code */
	unsigned short cnt = (unsigned short)1234;
	DDRD = 0xFF;
	DDRE = 0xFF;
	
    while (1) 
    {
		print_FND(cnt);
	}
}

void print_FND(unsigned short num){
	PORTE = 0x08;
	PORTD = num%10;
	num/=10;
	_delay_ms(1);
	PORTE = 0x04;
	PORTD = num%10;
	num/=10;
	_delay_ms(1);
	PORTE = 0x02;
	PORTD = num%10;
	num/=10;
	_delay_ms(1);
	PORTE = 0x01;
	PORTD = num%10;
	num/=10;
	_delay_ms(1);
	return;
}