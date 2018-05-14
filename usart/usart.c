
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart.h"

void USART_init(unsigned int baud){

	baud=(FOSC/16/baud-1);

	UBRR1H = (baud>>8); //Set baud Rate
	UBRR1L = baud;
	
	UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1); 
	UCSR1C = (1<<USBS1)|(1<<UCSZ11)|(1<<UCSZ10);
}

void USART_transmit(unsigned char data)
{

	PORTD1 = 1;
	if(!data) return;
	while ( !( UCSR1A & (1<<UDRE1)) );
	UDR1 = data;
	PORTD1= 0;
}

unsigned char USART_receive(void)
{

	while ( !(UCSR1A & (1<<RXC)) );
	return UDR1;
}
