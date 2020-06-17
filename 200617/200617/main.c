/*
 * 200617.c
 *
 * Created: 2020-06-17 오전 10:07:52
 * Author : user
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

unsigned char fnd_data[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6};

void fnd_control(unsigned char num)
{
	if(9<num) return;
	PORTA = ~fnd_data[num];
}

int main(void)
{
	unsigned char cnt = 0;
	DDRA = 0xFF;
	DDRC = 0x03;
	DDRD = 0x00;
	//PORTD = 0x00;
	unsigned char sw = 0;
	unsigned char cnt_time = 0;
    /* Replace with your application code */
    while (1) 
    {
		PORTC = 0x01;
		fnd_control(cnt%10);
		_delay_ms(5);
		PORTC = 0x02;
		fnd_control((cnt/10)%10);
		_delay_ms(5);
		if(!((PIND) & 0x01)) sw = 1;
		if(!((PIND) & 0x02)) sw = 2;
		cnt_time++;
		if(cnt_time == 50)
		{
			if(sw == 1)
			{
				cnt++;
				if(cnt == 100) cnt = 0;
			}
			if(sw == 2)
			{
				if(cnt == 0) cnt = 100;
				cnt--;
				if(cnt == -1) cnt = 99;
			}
			cnt_time = 0;
		}
    }
}

