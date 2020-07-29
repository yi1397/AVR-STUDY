/*
 * 200729.c
 *
 * Created: 2020-07-29 오전 10:21:30
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


void COMMAND(unsigned char byte)
{
	_delay_ms(2);
	
	PORTC = byte&0xF0;
	PORTC &= 0b11111100;
	_delay_us(1);
	PORTC |= 0b00000100;
	_delay_us(1);
	PORTC &= 0b11111011;
	
	
	PORTC = (byte<<4)&0xF0;
	PORTC &= 0b11111100;
	_delay_us(1);
	PORTC |= 0b00000100;
	_delay_us(1);
	PORTC &= 0b11111011;
}

void DATA(unsigned char byte)
{
	_delay_us(990);
	
	PORTC = byte&0xF0;
	PORTC |= 0b00000001;
	PORTC &= 0b11111101;
	
	_delay_us(1);
	PORTC |= 0b00000100;
	_delay_us(1);
	PORTC &= 0b11111011;
	
	
	PORTC = (byte<<4)&0xF0;
	PORTC |= 0b00000001;
	PORTC &= 0b11111101;
	
	_delay_us(1);
	PORTC |= 0b00000100;
	_delay_us(1);
	PORTC &= 0b11111011;
}

void LCD_INIT(void)
{
	_delay_ms(30);
	COMMAND(0b00101000);
	_delay_us(39);
	
	COMMAND(0b00001110);
	_delay_us(39);
	
	COMMAND(0b00000001);
	_delay_ms(1.53);
	
	COMMAND(0b00000110);
}

void MOVE(int y, int x)
{
	unsigned char data;
	if(y==1) data=0x7F+x;
	else data=0xBF+x;
	COMMAND(data);
}


void str_LCD(const char* str)
{
	for(int i = 0; i<strlen(str); i++)
	{
		DATA(str[i]);
	}
}

int main(void)
{
    /* Replace with your application code */
	
	ADMUX = 0x40;
	ADCSRA = 0x87;
	LCD_INIT();
    while (1) 
    {
		ADCSRA |= 0x40;
		while((ADCSRA & 0x10) != 0x10);
		
		char str[7];
		sprintf(str, "%d", (ADCH << 8) | ADCL);
		str_LCD("test");
    }
}

