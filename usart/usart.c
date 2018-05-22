#include "tbird.h"
#include "usart.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



void USART_init(unsigned int baud){

	baud=(F_CPU/16/baud-1);

	UBRR1H = (baud>>8); //Set baud Rate
	UBRR1L = baud;
	
	UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);   //RX enable // TX enable // RX interrupt enable
	UCSR1C = (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10);  // 1 start 1 stop 8 data bit

}

void USART_transmit(unsigned char data){

	if(!data) return;
	while ( !( UCSR1A & (1<<UDRE1)) );
	UDR1 = data;
}

unsigned char USART_receive(void){

	while ( !(UCSR1A & (1<<RXC)) );
	return UDR1;
}

void RS485_init(void){

	DE_DDR |= (1 << DE_PIN);
	RE_DDR |= (1 << RE_PIN); 
}

void RS485_busToTransmit(void){

	DE_PORT |= (1 << DE_PIN);
	RE_PORT |= (1 << RE_PIN);
}

void RS485_busToRecieve(void){

	DE_PORT &= ~(1 << DE_PIN);
	RE_PORT &= ~(1 << RE_PIN);
}