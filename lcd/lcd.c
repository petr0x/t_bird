#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define F_CPU 16000000UL;

void LCD_init(void){

	_delay_ms(20);
	//írány regiszterek beállítása
	DDRF |= 0x0E;
	DDRE |= 0xF0;

	_delay_ms(20);
	LCD_sendCommand(0x33);
	LCD_sendCommand(0x32);
	LCD_sendCommand(0x28);		// Init 4 bit
	LCD_sendCommand(0x0C);
	LCD_sendCommand(0x01);

	_delay_ms(100);


}	

void LCD_sendEnable(void){
	_delay_ms(1);
	CTRL |= 0b0001000;
	_delay_ms(1);
	CTRL &= 0b11110111;
}

void LCD_sendCommand(unsigned char command){
	// RS 0-ba
	CTRL &=  0xFD;
	// data ra a command felső 4 bite
	DATA = (command&0xF0);
	LCD_sendEnable();
	// data ra a command also 4 bite
	DATA = ((command<<4)&0xF0);
	LCD_sendEnable();

}

void LCD_sendData(unsigned char data){
	CTRL |= 0b00000010;
	DATA = data&0xF0;
	LCD_sendEnable();
	DATA = ((data<<4)&0xF0);
	LCD_sendEnable();
}

void LCD_sendString(unsigned char *str){
	unsigned char i;
	for(i = 0; str[i] != 0; i++){
		LCD_sendData(str[i]);
	}
}

void LCD_setCursor(unsigned char row, unsigned char pos){
	if(row < 4 && pos < 16){
		switch(row){
			case 0: LCD_sendCommand(0x80+pos); break;
			case 1: LCD_sendCommand(0xC0+pos); break;
			case 2: LCD_sendCommand(0x90+pos); break;
			case 3: LCD_sendCommand(0xD0+pos); break;
		}
	}
}

void LCD_clrearScreen(void){
	LCD_sendCommand(0x01);
	LCD_setCursor(0,0);
}