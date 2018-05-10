#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "lcd.h"
#include "tbird.h"
#include "usart.h"

#define F_CPU 16000000UL;

int main(){
	LCD_init();
	LCD_sendData(238);
	while(1){}
}
