/*
 * GccApplication1.c
 *
 * Created: 2020-05-30 오후 1:11:18
 * Author : user
 */ 

#include <avr/io.h>

void show_FND(unsigned short num);

int main(void)
{
    /* Replace with your application code */
	DDRD = 0xFF;
	DDRC = 0xFF;
	
	unsigned short number_FND = 2314;
	
    while (1) 
    {
		show_FND(number_FND);
    }
}

void show_FND(unsigned short num)
{
	unsigned char buff = 0x00;
	buff = num%10;
	num /= 10;
	buff |= (num % 10) << 4;
	num /= 10;
	PORTC = buff;
	buff = 0x00;
	buff = num%10;
	num /= 10;
	buff |= (num % 10) << 4;
	num /= 10;
	PORTD = buff;
	return;
}

