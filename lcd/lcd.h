#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#define DATA PORTE
#define CTRL PORTF

void LCD_init(void);
void LCD_sendEnable(void);
void LCD_sendCommand(unsigned char command);
void LCD_sendData(unsigned char data);
void LCD_sendString(unsigned char *str);
void LCD_setCursor(unsigned char row, unsigned char pos);
void LCD_clearScreen(void);
void LCD_isBusy(void);
#endif
