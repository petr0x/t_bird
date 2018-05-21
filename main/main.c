#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "tbird.h"
#include "lcd.h"
#include "usart.h"
#include "fifo.h"


void init(void);
void selectRole(void);

char role = 0;

static FIFO recive;
static unsigned char reciveArray[64]; 

int main(){

	init();

	selectRole();

	sei();

	while(1){
		_delay_ms(100000);
		LCD_sendData(FIFO_getElement(&recive));

	}
}

void init(void){
	init_tbird();
	LCD_init();
	USART_init(9600);
	FIFO_init(&recive,reciveArray,64);
	DDRD |= 0x03;
	PORTD &= 0xFC;
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
			// RX complete interrupt
	UCSR1B &= ~(1<<RXCIE1);

	FIFO_storeElement(&recive, UDR1);
	
	UCSR1B |= (1<<RXCIE1);
}
