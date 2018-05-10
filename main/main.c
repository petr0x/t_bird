#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "lcd.h"
#include "tbird.h"
#include "usart.h"

#define F_CPU 16000000UL;

void init(void);
char selectRole(void);

char role = 0;

int main(){
	init();

	while(!role){
		role = selectRole();
		while(1){}
	}


	while(1){
		
	}
}

void init(void){
	init_tbird();
	LCD_init();
	USART_init(9600);
}

char selectRole(void){
	LCD_sendString("K0: Push Buttons");
	LCD_setCursor(1,0);
	LCD_sendString("K1: Matrix");
	LCD_setCursor(2,0);
	LCD_sendString("K2: LEDs");
	LCD_setCursor(3,0);
	LCD_sendString("K3: LCD");
}
