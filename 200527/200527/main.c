/*
 * 200527.c
 *
 * Created: 2020-05-27 오전 11:32:59
 * Author : user
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

  char number_FND[10][8] = {
	{1,1,1,1,1,1,0,0}, //0
	{0,1,1,0,0,0,0,0}, //1
	{1,1,0,1,1,0,1,0}, //2
	{1,1,1,1,0,0,1,0}, //3
	{0,1,1,0,0,1,1,0}, //4
	{1,0,1,1,0,1,1,0}, //5
	{1,0,1,1,1,1,1,0}, //6
	{1,1,1,0,0,0,0,0}, //7
	{1,1,1,1,1,1,1,0}, //8
	{1,1,1,1,0,1,1,0}, //9
  };

unsigned char buff_FND(unsigned char num);
void print_FND(unsigned short num);

int main(void)
{
    /* Replace with your application code */
	unsigned short cnt = (unsigned short)919;
	DDRA = 0xFF; //FND 자릿수 제어용
	DDRF = 0xFF;
	
    while (1) 
    {
		print_FND(cnt);
	}
}

unsigned char buff_FND(unsigned char num)
{	
	unsigned char buff = 0x00;
	if(9<num) return buff;
	buff |= number_FND[num][0]<<0;
	buff |= number_FND[num][1]<<1;
	buff |= number_FND[num][2]<<2;
	buff |= number_FND[num][3]<<3;
	buff |= number_FND[num][4]<<4;
	buff |= number_FND[num][5]<<5;
	buff |= number_FND[num][6]<<6;
	buff |= number_FND[num][7]<<7;
	
	return buff;
}

void print_FND(unsigned short num){
	unsigned char buff;
	buff = buff_FND(num%10);
	num/=10;
	PORTA = 0x08;
	PORTF = buff;
	_delay_ms(1);
	buff = buff_FND(num%10);
	num/=10;
	PORTA = 0x04;
	PORTF = buff;
	_delay_ms(1);
	buff = buff_FND(num%10);
	num/=10;
	PORTA = 0x02;
	PORTF = buff;
	_delay_ms(1);
	buff = buff_FND(num%10);
	num/=10;
	PORTA = 0x01;
	PORTF = buff;
	_delay_ms(1);
	return;
}