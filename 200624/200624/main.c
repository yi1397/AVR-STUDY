/*
 * 200624.c
 *
 * Created: 2020-06-24 오전 10:08:58
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

int main(void)
{
    /* Replace with your application code */
    DDRC = 0xFF;
	DDRD = 0x00;
	PORTC = 0x00;
	LCD_INIT();
	
	unsigned char x=1;
	
	str_LCD("0000");
	
	unsigned char num[5] = {0,0,0,0};
	
    while (1) 
    {
		if(!(PIND & 0x01))
		{
			if(x!=1)
			{
				x--;
			}
		}
		else if(!(PIND & 0x02))
		{
			if(x!=4)
			{
				x++;
			}
		}
		if(!(PIND & 0x04))
		{
			if (num[x]!=9)
			{
				
				DATA('0'+(++num[x]));
			}
		}
		if(!(PIND & 0x08))
		{
			if (num[x]!=0)
			{
				
				DATA('0'+(--num[x]));
			}
		}
		
		MOVE(1,x);
		_delay_ms(200);
    }
}

