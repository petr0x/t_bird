#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

void USART_init(unsigned int baud);
void USART_transmit(unsigned char data);
unsigned char USART_receive(void);

#endif
