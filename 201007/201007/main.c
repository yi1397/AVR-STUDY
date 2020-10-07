/*
 * 201007.c
 *
 * Created: 2020-10-07 오전 11:07:13
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define DHT11_PIN 6
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

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

void Request()				// ATMega128로 스타트 펄스 전달 & 응답 과정
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);	// PD4 LOW
	_delay_ms(20);
	PORTD |= (1<<DHT11_PIN);	// PD4 HIGH
}
void Response()				// 온습도 센서로부터 응답
{
	DDRD &= ~(1<<DHT11_PIN); // PD4 LOW
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_data()
{
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0); //비트가 0인지 1인지 체크
		_delay_us(30);
		if(PIND & (1<<DHT11_PIN)) //HIGH가 30ms보다 크면
		c = (c<<1)|(0x01);	 //HIGH 상태
		else
		c = (c<<1); //LOW 상태
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}


int main(void)
{
    /* Replace with your application code */
	DDRC = 0xFF;
	PORTC = 0x00;
	LCD_INIT();
	
    while (1) 
    {
		Request();		 //시작 펄스 신호 보냄
		Response();		 //센서로부터 응답 받음
		I_RH=Receive_data();	 //습도의 정수 부분
		D_RH=Receive_data();	 //습도의 실수 부분
		I_Temp=Receive_data();	 //온도의 정수 부분
		D_Temp=Receive_data();	 //온도의 실수 부분
		CheckSum=Receive_data(); //모든 세그먼트의 체크섬
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			str_LCD("err");
		}
		else
		{
			char data[11];
			MOVE(1,1);
			str_LCD("RH:");
			MOVE(1,5);
			itoa(I_RH,data,10);
			str_LCD(data);
			MOVE(2,1);
			str_LCD("T:");
			MOVE(2,5);
			itoa(I_Temp,data,10);
			str_LCD(data);
		}
		_delay_ms(3000);
		//COMMAND(0b00000001);
		//_delay_ms(2);
    }
}

