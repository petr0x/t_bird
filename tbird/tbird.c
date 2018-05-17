#include "tbird.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void init_tbird(){
	
	DDRB = DDRD = 0xF0; // Ledek kimenetbe állítása
	DDRA = 0xFF;		// 7 szegmens kiement
	DDRC = 0xF8;		// RED kimenet sorok kimenet, oszlopok bemenet
	DDRG = 0xE0;		// Gombok bemenet

}

void showOnLed(unsigned char x){

	PORTD = x;
	PORTB = (x << 4);
}

unsigned char matrixValue(){
	
	char row;
	char state = 0;
	char value = 0;

	for(row = 8; row < 128; row <<= 1){

		PORTC = (row&0b01111000);

		_delay_ms(10);

		switch((~PINC) & 0b111){
			case 1:
				if(!state){
					if(row == 8) value = '1';
					else if(row == 16) value = '4';
					else if(row == 32) value = '7';
					else if(row == 64) value = '*';
					
					state = 1;
					break;
	 
				}
			case 2:
				if(!state){
					if(row == 8) value = '2'; 
					else if(row == 16) value = '5';
					else if(row == 32) value = '8';
					else if(row == 64) value = '0';
				
					state = 1;
					break;
				}
			case 4:
				if(!state){
					if(row == 8) value = '3'; 
					else if(row == 16) value = '6';
					else if(row == 32) value = '9';
					else if(row == 64) value = '#';
				
					state = 1;
					break;
				}
			default:
				state = 0;
				break;
		}
		if(state && value) return value;
	}
	
	return 0;
}

unsigned char readButton(){

	return (PING & 0x1F);

}

