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
   
    char key_store[4]; // Array to store the pressed keys
    int count = 0; // Counter for stored keys
    char last_key = '\0'; // Variable to track the last key pressed

    while (1) {
        key = keypad_read(); // Read the key from the keypad
        if (key && key != last_key) { // Check if a key is pressed and it's different from the last key
            lcd_command(0x01); // Clear the LCD
            _delay_ms(2);
	   
            key_str[0] = key; 
            key_str[1] = '\0'; // Null-terminate the string

            if (key != '*') {
                // Store the key if it's not '*'
                if (count < sizeof(key_store) - 1) { // Ensure we don't overflow the array
                    key_store[count] = key;
                    count++;
                }
            } else {
                // If '*' is pressed, display the stored keys
                key_store[count] = '\0'; // Null-terminate the stored keys
                lcd_command(0x01); // Clear the LCD again before printing
                _delay_ms(2);
                lcd_print(key_store); // Print the stored keys

                // Wait for a moment to see the output
                // _delay_ms(2000); // Wait for 2 seconds to see the output

                // Empty the key_store array
	        int i = 0;
                for (i = 0; i < sizeof(key_store); i++) {
                    key_store[i] = '\0'; // Set each element to null character
                }
                count = 0; // Reset the count
            }

            // Update the last key pressed
            last_key = key;
        } else if (!key) {
            // Reset last_key when no key is pressed
            last_key = '\0';
        }
    }
}
