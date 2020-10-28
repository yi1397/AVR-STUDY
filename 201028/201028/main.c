/*
 * 201028.c
 *
 * Created: 2020-10-28 오전 11:30:16
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util./delay.h>
#include <avr/interrupt.h>

#define SCORE_SIZE 9

unsigned char cnt = 0;
unsigned char score[SCORE_SIZE] = {17, 43, 66, 77, 97, 114, 127, 137, 255};

ISR(TIMER0_OVF_vect)
{
	PORTB ^= 0x20;
	TCNT0 = score[cnt];
}

int main(void)
{
    /* Replace with your application code */
    DDRB=0x20;
	TCCR0 =0x03;
	TIMSK = 0x01;
	sei();

    while(1){
		if(PINB & 0x01)
		{
			cnt = (cnt + 1) % SCORE_SIZE;
			_delay_ms(300);
		}
    }

}

