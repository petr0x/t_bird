#include "FIFO.h"

void FIFO_init(FIFO *fifo, unsigned char *array, unsigned char size){

	fifo -> array = array;
	fifo -> bufferSize = size-1;
	fifo -> readIndex = 0;
	fifo -> writeIndex = 0;
	fifo -> numberOfElements = 0;
}

unsigned char FIFO_getElement(FIFO *fifo){

	if(!fifo->numberOfElements) return 0;

	unsigned char data;

	data = fifo -> array[fifo -> readIndex];
	fifo -> readIndex %= fifo -> numberOfElements;
	fifo -> numberOfElements--;

	return data;
}

unsigned char FIFO_storeElement(FIFO *fifo, unsigned char data){

	if(fifo -> bufferSize == fifo -> numberOfElements) return 0;

	fifo -> array[writeIndex] = data;
	fifo -> writeIndex++;
	fifo -> writeIndex %= fifo-> bufferSize;
	fifo -> numberOfElements++;

	return 1;
}
