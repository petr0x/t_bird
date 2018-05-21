#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "tbird.h"
#include "usart.h"


void USART_init(unsigned int baud){

	baud=(F_CPU/16/baud-1);

	UBRR1H = (baud>>8); //Set baud Rate
	UBRR1L = baud;
	
	UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);   //RX enable // TX enable // RX interrupt enable
	UCSR1C = (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10);  // 1 start 1 stop 8 data bit
}

void USART_transmit(unsigned char data)
{

	if(!data) return;
	while ( !( UCSR1A & (1<<UDRE1)) );
	UDR1 = data;
}

unsigned char USART_receive(void)
{

	while ( !(UCSR1A & (1<<RXC)) );
	return UDR1;
}
