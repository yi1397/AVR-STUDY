/*
 * 200701.c
 *
 * Created: 2020-07-01 오전 10:15:13
 * Author : user
 */ 

#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)

#include <avr/io.h>
#include <util/delay.h>

void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void uart_write(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char uart_read()
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

int main(void)
{
    /* Replace with your application code */
	
	uart_init(BAUDRATE(9600));
	
    while (1) 
    {
		unsigned char ch = uart_read();
		if ('a' <= ch && ch <= 'z')
		{
			uart_write(ch - 'a' + 'A');
		}
		else
		{
			uart_write(ch);
		}
    }
}

