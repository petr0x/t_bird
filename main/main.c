#define TBIRD3

#include "tbird.h"
#include "lcd.h"
#include "usart.h"
#include "fifo.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>



void init(void);
void selectRole(void);

unsigned char role = 0, i;

FIFO recieve;
unsigned char recieveArray[50]; 

int main(){

	init();

	selectRole();

	sei();

	LCD_clearScreen();
	while(1){
		if(role == 1){
			for(i = 'a'; i<= 'f'; i++){
				USART_transmit(i);
				_delay_ms(500);
			}
		}
		else{
			_delay_ms(600);
			i = FIFO_getElement(&recieve);
			if(!i) continue;
			LCD_sendData(i);
		}
	}
}

void init(void){
	init_tbird();
	LCD_init();
	USART_init(9600);
	RS485_init();
	FIFO_init(&recieve,recieveArray,50);
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
			RS485_busToTransmit();
		}break;

		case 2:{
			LCD_sendString("Matrix");
			RS485_busToRecieve(); 
		}break;

		case 4:{
			LCD_sendString("LEDs");
			RS485_busToRecieve();  
		}break;

		case 8:{
			LCD_sendString("LCD");
			RS485_busToRecieve();  
		}break;
	}
}

ISR(USART1_RX_vect){

	FIFO_storeElement(&recieve, UDR1);
	
}
