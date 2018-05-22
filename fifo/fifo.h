#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

typedef struct{

	unsigned char* array;
	unsigned char bufferSize;
	unsigned char readIndex;
	unsigned char writeIndex;
	unsigned char numberOfElements;

	
}FIFO;

void FIFO_init(FIFO *, unsigned char *, unsigned char);
unsigned char FIFO_getElement(FIFO *);
unsigned char FIFO_storeElement(FIFO *, unsigned char);

#endif
