#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"

int main(void) {
    lcd_init(); // Initialize the LCD
    lcd_print("Press a key:"); // Print an initial message
    _delay_ms(1000);
      
    keypad_init();
    char key;
    char key_str[2]; // Array to hold the key as a string
   

    while (1) {
        key = keypad_read();
        if (key) {
            // Convert the key to a string
            key_str[0] = key;  // Set the first character
            key_str[1] = '\0'; // Null-terminate the string
	   
            
            lcd_command(0x01); // Clear the LCD
            _delay_ms(2); // Small delay to allow the clear command to execute
            lcd_print(key_str); // Print the key pressed
            
            // Optional: You can add a small delay
            // _delay_ms(1000); // Wait for a second before reading next key
        }
    }
}
