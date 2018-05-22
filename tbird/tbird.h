#ifndef TBIRD_H_INCLUDED
#define TBIRD_H_INCLUDED

#ifdef TBIRD3

#define F_CPU 8000000UL

#else 

#define F_CPU 16000000UL

#endif

void init_tbird(void);
void showOnLed(unsigned char);
unsigned char matrixValue();
unsigned char readButton();

#endif
