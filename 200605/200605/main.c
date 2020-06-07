/*
 * 200605.c
 *
 * Created: 2020-06-05 오후 4:44:41
 * Author : user
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

unsigned short output_order_FND[4] = {0x0800, 0x8000, 0x0008, 0x0080};

unsigned char pin_LATCH = 0x01;
unsigned char pin_CLOCK = 0x02;
unsigned char pin_DATA = 0x04;

void FND_print(unsigned int num);

int main(void)
{
    /* Replace with your application code */
    DDRB = 0x07;
	
	unsigned int cnt = 0;
	
	PORTB = 0x00;
	
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
	
	PORTB = 0x00;
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++){
			if(buff & (output_order_FND[i] >> j)) PORTB = PORTB | pin_DATA;
			else PORTB = PORTB &~ pin_DATA;
			PORTB = PORTB | pin_CLOCK;
			_delay_us(100);
			PORTB = 0x00;
			_delay_us(100);
		}
	}
	
	PORTB = pin_LATCH;
	
	
	return;
}

