// lcd.c
#include "lcd.h"
#include <util/delay.h>

void lcd_command(unsigned char cmd) {
    PORTA &= ~(1 << LCD_RS); // RS = 0 for command
    PORTA &= ~(1 << LCD_RW); // RW = 0 for write
    PORTA |= (1 << LCD_E);   // Enable high

    // Send higher nibble
    PORTA = (PORTA & 0x0F) | (cmd & 0xF0); // Mask lower nibble
    PORTA &= ~(1 << LCD_E); // Enable low
    _delay_us(100);         // Delay for command execution

    PORTA |= (1 << LCD_E);  // Enable high
    // Send lower nibble
    PORTA = (PORTA & 0x0F) | ((cmd << 4) & 0xF0); // Mask lower nibble
    PORTA &= ~(1 << LCD_E); // Enable low
    _delay_us(100);         // Delay for command execution
}

void lcd_data(unsigned char data) {
    PORTA |= (1 << LCD_RS);  // RS = 1 for data
    PORTA &= ~(1 << LCD_RW); // RW = 0 for write
    PORTA |= (1 << LCD_E);   // Enable high

    // Send higher nibble
    PORTA = (PORTA & 0x0F) | (data & 0xF0); // Mask lower nibble
    PORTA &= ~(1 << LCD_E); // Enable low
    _delay_us(100);         // Delay for data execution

    PORTA |= (1 << LCD_E);  // Enable high
    // Send lower nibble
    PORTA = (PORTA & 0x0F) | ((data << 4) & 0xF0); // Mask lower nibble
    PORTA &= ~(1 << LCD_E); // Enable low
    _delay_us(100);         // Delay for data execution
}

void lcd_init() {
    DDRA = 0xFF; // Set PORTA as output
    _delay_ms(20); // Wait for LCD to power up

    // Initialize LCD in 4-bit mode
    lcd_command(0x33); // Initialize
    lcd_command(0x32); // Set to 4-bit mode
    lcd_command(0x28); // 2 lines, 5x7 matrix
    lcd_command(0x0C); // Display ON, Cursor OFF
    lcd_command(0x06); // Increment cursor
    lcd_command(0x01); // Clear display
    _delay_ms(2);      // Wait for clear command to finish
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}
