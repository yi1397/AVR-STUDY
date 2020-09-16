/*
 * 200916.c
 *
 * Created: 2020-09-16 오전 10:30:15
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char motor_speed = 0;

int main(void)
{
    /* Replace with your application code */
	DDRB = 0x10;
    DDRD = 0xFF;
	DDRG = 0x00;
	
	TCCR0 |= (1<<CS02);
	
	TCCR0 |= (1<<WGM01);
	TCCR0 |= (1<<WGM00);
	
	TCCR0 |= (1<<COM01);
	
	TCNT0 = 0;
	
	PORTD = 0x01;
	
    while (1) 
    {
		if(!(PING & 0x01))
		{
			//up
			if(motor_speed != 5) 
			{
				motor_speed++;
				PORTD = PORTD << 1 | 1;
			}
		}
		else if(!(PING & 0x02))
		{
			//down
			if(motor_speed != 0) 
			{
				motor_speed--;
				PORTD = PORTD >> 1;
			}
		}
		else if(!(PING & 0x04))
		{
			//stop
			motor_speed = 0;
			PORTD = 0x01;
		}
		OCR0 = motor_speed ? 105 + motor_speed * 30 : 0;
		_delay_ms(100);
    }
}

