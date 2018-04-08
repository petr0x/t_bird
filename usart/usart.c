
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FOSC 16000000// Órajel
#define BAUD 9600// Baud rate
#define MYUBRR FOSC/16/BAUD-1 //USART Init data (catalog)


void init(void);
unsigned char matrixValue(void);
void showOnLed(unsigned char);

void USART_Init(unsigned int baud);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);

int main(void){
	USART_Init (MYUBRR);
	init();

	for(;;){
		USART_Transmit(matrixValue());
		showOnLed(USART_Receive());
	}
}

void init(void){
	
	DDRB = DDRD = 0xF0; // Ledek kimenetbe állítása
	DDRA = 0xFF;		// 7 szegmens kiement
	DDRC = 0xF8;		// RED kimenet sorok kimenet, oszlopok bemenet
	DDRG = 0xE0;		// Gombok bemenet
}

unsigned char matrixValue(void){
	
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

void showOnLed(unsigned char x){

	PORTD = x;
	PORTB = (x << 4);
}

void USART_Init(unsigned int baud){

	UBRR0H = (baud>>8); //Set baud Rate
	UBRR0L = baud;
	
	UCSR0B = (1<<RXEN)|(1<<TXEN); 
	UCSR0C = (1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit(unsigned char data)
{

	if(!data) return;
	while ( !( UCSR0A & (1<<UDRE)) );
	UDR0 = data;
}

unsigned char USART_Receive(void)
{

	while ( !(UCSR0A & (1<<RXC)) );
	return UDR0;
}