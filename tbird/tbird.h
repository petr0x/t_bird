#ifndef TBIRD_H_INCLUDED
#define TBIRD_H_INCLUDED

#define F_CPU 16000000UL

void init_tbird(void);
void showOnLed(unsigned char);
unsigned char matrixValue();
unsigned char readButton();

#endif
