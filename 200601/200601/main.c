/*
 * 200601.c
 *
 * Created: 2020-06-01 오전 9:20:34
 * Author : user
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

unsigned char pin_LATCH = 0x01;
unsigned char pin_CLOCK = 0x02;
unsigned char pin_DATA = 0x04;

void FND_print(unsigned int num);

int main(void)
{
    /* Replace with your application code */
    DDRC = 0x07;
	
	unsigned int cnt = 0;
	
    while (1) 
    {
		cnt++;
		FND_print(cnt);
		_delay_ms(1000);
    }
}

void FND_print(unsigned int num)
{
	unsigned int buff = 0x00;
	
	buff = num%10;
	num /= 10;
	buff |= (num % 10) << 4;
	num /= 10;
	buff |= (num % 10) << 8;
	num /= 10;
	buff |= (num % 10) << 12;
	num /= 10;
	
	PORTC |= pin_LATCH;
	for(int i = 8; i < 16; i++){
		if(buff & (0x01 << i)) PORTC = PORTC | pin_DATA;
		else PORTC = PORTC &~ pin_DATA;
		PORTC = PORTC | pin_CLOCK;
		_delay_us(100);
		PORTC = PORTC &~ pin_CLOCK;
		_delay_us(100);
	}
	PORTC |= pin_LATCH;
	
	PORTC &=~ pin_LATCH;
	for(int i = 0; i < 8; i++){
		if(buff & (0x01 << i)) PORTC = PORTC | pin_DATA;
		else PORTC = PORTC &~ pin_DATA;
		PORTC = PORTC | pin_CLOCK;
		_delay_us(100);
		PORTC = PORTC &~ pin_CLOCK;
		_delay_us(100);
	}
	
	return;
}