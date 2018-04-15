#define F_CPU 16000000UL;

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>

void LCD_init(void){

	_delay_ms(20);
	DDRF = 0x0E
	DDRE = 0xF0;
	LCD_sendCommand(0x30);
	_delay_ms(5);
	LCD_sendCommand(0x30);
	_delay_ms(2);
	LCD_sendCommand(0x30);
	_delay_ms(2000);
	LCD_sendCommand(0b00001110);
	LCD_sendCommand(0x02);
	LCD_sendCommand(0x06);
	LCD_sendCommand(0x01);
	LCD_sendCommand(0x0C);

}	

void LCD_sendEnable(void){
	_delay_ms(1);
	ENABLE = 1;
	_delay_ms(1);
	ENABLE = 0;
}

void LCD_sendCommand(unsigned char command){
	PORTF &=  0xFD;
	PORTE = (command&0xF0);
	LCD_sendEnable();
	PORTE = ((command<<4)&0xF0);
	LCD_sendEnable();

}

void LCD_sendData(unsigned char data){
	PORTF |= 0b00000010;
	PORTE = data&0xF0;
	LCD_sendEnable();
	adat = (data<<4);
	PORTE = data&0xF0;
	LCD_sendEnable();
}
