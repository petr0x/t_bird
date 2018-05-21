#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

void USART_init(unsigned int);
void USART_transmit(unsigned char);
unsigned char USART_receive(void);

#endif
