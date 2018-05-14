#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#define DATA PORTE
#define CTRL PORTF
#define BUSY PORTE7
#define ENABLE PORTF3
#define RW PORTF2
#define RS PORTF1

void LCD_init(void);
void LCD_sendEnable(void);
void LCD_sendCommand(unsigned char command);
void LCD_sendData(unsigned char data);
void LCD_sendString(unsigned char *str);
void LCD_setCursor(unsigned char row, unsigned char pos);
void LCD_clearScreen(void);
void LCD_waitBusy(void);
#endif
