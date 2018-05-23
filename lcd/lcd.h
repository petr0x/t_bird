#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#define DATA PORTE
#define CTRL PORTF
#define ENABLE PORTF3
#define RW PORTF2
#define RS PORTF1

void LCD_init(void);
void LCD_sendEnable(void);
void LCD_sendCommand(unsigned char);
void LCD_sendData(unsigned char);
void LCD_sendString(char*);
void LCD_setCursor(unsigned char, unsigned char);
void LCD_clearScreen(void);
void LCD_waitBusy(void);
#endif
