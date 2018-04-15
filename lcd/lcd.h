#ifndef LCD_TBIRD_H_INCLUDED
#define LCD_TBIRD_H_INCLUDED

#define RS PF1
#define RW PF2
#define ENABLE PF3
#define DB7 PE7
#define DB6 PE6
#define DB5 PE5
#define DB4 PE4

void LCD_init(void);
void LCD_sendEnable(void);
void LCD_sendCommand(unsigned char command);
void LCD_sendData(unsigned char data);
#endif