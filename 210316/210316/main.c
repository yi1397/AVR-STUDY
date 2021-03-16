/*
 * 210316.c
 *
 * Created: 2021-03-16 오후 9:33:52
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

void GLCD_Command(unsigned char cmd)
{
	PORTC = cmd;
	PORTA &= ~0x01;
	PORTA &= ~0x02;
	PORTA |=  0x04;
	_delay_us(5);
	PORTA &= ~0x04;
	_delay_us(5);
}

void GLCD_Data(unsigned char data)
{
	PORTC = data;
	PORTA |= ~0x01;
	PORTA &= ~0x02;
	PORTA |=  0x04;
	_delay_us(5);
	PORTA &= ~0x04;
	_delay_us(5);
}

void GLCD_Init()
{
	PORTA |= 0x38;
	_delay_ms(20);
	GLCD_Command(0x3E);
	GLCD_Command(0x40);
	GLCD_Command(0xB8);
	GLCD_Command(0xC0);
	GLCD_Command(0x3F);
}

void GLCD_ClearAll()
{
	int i,j;
	PORTA |= 0x18;
	for(i = 0; i < 2; i++)
	{
		GLCD_Command((0xB8) + i);
		for(j = 0; j < 64; j++)
		{
			GLCD_Data(0x11);
		}
	}
	GLCD_Command(0x40);
	GLCD_Command(0xB8);
}

int main(void)
{
    /* Replace with your application code */
    DDRA = 0x07;
    DDRC = 0xFF;
	GLCD_Init();
	
	GLCD_Data(0x02);
	GLCD_ClearAll();
    while (1) 
    {
    }
}

