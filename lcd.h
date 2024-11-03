// lcd.h
#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

#define LCD_RS PA0
#define LCD_RW PA1
#define LCD_E  PA2
#define LCD_D4 PA4
#define LCD_D5 PA5
#define LCD_D6 PA6
#define LCD_D7 PA7

void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_print(const char *str);

#endif // LCD_H
