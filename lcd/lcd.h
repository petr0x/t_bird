#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#define RS PF1
#define RW PF2
#define ENABLE PF3
#define DATA PORTE
#define CTRL PORTF
#define DB7 PE7
#define DB6 PE6
#define DB5 PE5
#define DB4 PE4

void LCD_init(void);
void LCD_sendEnable(void);
void LCD_sendCommand(unsigned char command);
void LCD_sendData(unsigned char data);
void LCD_sendString(unsigned char *str);
void LCD_setCursor(unsigned char row, unsigned char pos);
void LCD_clearScreen(void);
#endif
