#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "lcd.h"
#include "tbird.h"
#include "usart.h"

#define F_CPU 16000000UL

void init(void);
void selectRole(void);

char role = 0;

int main(){

	init();

	selectRole();
	sei();

	while(1){
		USART_transmit(matrixValue());
	}
}

void init(void){
	init_tbird();
	LCD_init();
	USART_init(9600);
	DDRD |= 0x03;
	PORTD0 = 1;
}

void selectRole(){
	LCD_sendString("K0: Push Buttons");
	LCD_setCursor(1,0);
	LCD_sendString("K1: Matrix");
	LCD_setCursor(2,0);
	LCD_sendString("K2: LEDs");
	LCD_setCursor(3,0);
	LCD_sendString("K3: LCD");

	while(!role){
		role=readButton();
		if(role != 1 && role != 2 && role != 4 && role != 8){
			role = 0;
		}
	}

	LCD_clearScreen();
	LCD_sendString("Selected role:");
	LCD_setCursor(1,0);
	switch(role){
		case 1:{
			LCD_sendString("Push Buttons");
			LCD_setCursor(2,0);
			LCD_sendString("Press K0");
			LCD_setCursor(3,0);
			LCD_sendString("to start RS485");
		}break;
		case 2: LCD_sendString("Matrix"); break;
		case 4: LCD_sendString("LEDs"); break;
		case 8: LCD_sendString("LCD"); break;
	}
}

ISR(USART1_RX_vect){
	UCSR1B &= ~(1<<RXCIE1);

	LCD_clearScreen();
	LCD_sendData(USART_receive());
	LCD_setCursor(0,0);
	
	UCSR1B |= (1<<RXCIE1);
}
