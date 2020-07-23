/*
 * 200723.c
 *
 * Created: 2020-07-23 오전 9:21:30
 * Author : user
 */ 

#define F_CPU 16000000UL
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

void func1()
{
	PORTE = PORTE == 0xFF ? ~0x01 : (PORTE << 1) + 1;
}

void func2()
{
	PORTE = PORTE == 0xFF ? ~0x80 : (PORTE >> 1) + 0x80;
}

void (*funcs[2])() = {func1, func2};
	
char str[][2] = {" R", " L"};

int main(void)
{
    /* Replace with your application code */
	
	DDRC = 0xFF;
	DDRD = 0x00;
	DDRE = 0xFF;
	PORTC = 0x00;
	PORTE = ~0x01;
	LCD_INIT();
	
	int set = 1;
	
    while (1) 
    {
		if(!(PIND & 0x01))
		{
			if(set!=0)
			{
				set--;
			}
		}
		else if(!(PIND & 0x02))
		{
			if(set!=1)
			{
				set++;
			}
		}
		
		COMMAND(0b00000001);
		if(set == 0)
		{
			str_LCD(" RIGHT");
		}
		if(set == 1)
		{
			str_LCD(" LEFT");
		}
		funcs[set]();
		_delay_ms(100);
    }
}

