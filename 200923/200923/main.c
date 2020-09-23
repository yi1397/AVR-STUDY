/*
 * 200923.c
 *
 * Created: 2020-09-23 오전 10:03:55
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

unsigned int dist;

int main(void)
{
    /* Replace with your application code */
	DDRD = 0xFF;
	DDRE = ((DDRE | (1<<TRIG)) & ~(1<<ECHO));
    while (1) 
    {
		TCCR1B = 0x03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		PORTE |= (1<<TRIG);
		_delay_us(10);
		PORTE &= ~(1<<TRIG);
		while(!(PINE & (1<<ECHO)));
		TCNT1 = 0x0000;
		while(PINE & (1<<ECHO));
		TCCR1B = 0x00;

		dist = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 2) / 1000);
		
		PORTD = 0x01 <<
			((30 < dist)
			+ (70 < dist) 
			+ (100 < dist) 
			+ (130 < dist) 
			+ (200 < dist));
		_delay_ms(100);
    }
}

