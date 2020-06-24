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
	
	COMMAND(0b00001100);
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
	
	unsigned char cnt_go = 0;
	
	unsigned long cnt = 0;
	
	unsigned long time_cnt = 9999;
    while (1) 
    {
	    COMMAND(0b00000010);
		MOVE(1,7);
		str_LCD("TIME");
		
		MOVE(2,5);
		DATA((cnt/100000)%10 + '0');
		DATA((cnt/10000)%10 + '0');
		DATA(':');
	    DATA((cnt/1000)%10 + '0');
	    DATA((cnt/100)%10 + '0');
		DATA(':');
	    DATA((cnt/10)%10 + '0');
		DATA(cnt%10 + '0');
		_delay_ms(6);
		if(cnt_go == 1)
		{
			 cnt+=2;
		}
		time_cnt+=2;
		if(cnt == 1000000) cnt = 0;
		
		
		if((!(PIND & 0x01)) & 100 < time_cnt)
		{
			 cnt_go = !cnt_go;
			 time_cnt = 0;
		}
		if((!(PIND & 0x02)) & 50 < time_cnt)
		{
			cnt_go = 0;
			cnt = 0;
			time_cnt = 0;
		}
    }
}

