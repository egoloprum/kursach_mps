#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"

void convert_to_letters(char* key_store, int count) {
    char result[20]; // Buffer to hold the resulting letters
    int j = 0; // Index for the result array

    int i = 0;
    for (i = 0; i < count; i++) {
        char key = key_store[i];
        int press_count = 1;

        // Count how many times the same key is pressed
        while (i + 1 < count && key_store[i + 1] == key) {
            press_count++;
            i++;
        }

        // Map the key and press count to the corresponding letter
        if (key == '2') {
            result[j++] = 'A' + (press_count - 1) % 3; // a, b, c
        } else if (key == '3') {
            result[j++] = 'D' + (press_count - 1) % 3; // d, e, f
        } else if (key == '4') {
            result[j++] = 'G' + (press_count - 1) % 3; // g, h, i
        } else if (key == '5') {
            result[j++] = 'J' + (press_count - 1) % 3; // j, k, l
        } else if (key == '6') {
            result[j++] = 'M' + (press_count - 1) % 3; // m, n, o
        } else if (key == '7') {
            result[j++] = 'P' + (press_count - 1) % 4; // p, q, r, s
        } else if (key == '8') {
            result[j++] = 'T' + (press_count - 1) % 3; // t, u, v
        } else if (key == '9') {
            result[j++] = 'W' + (press_count - 1) % 4; // w, x, y, z
        }
    }

    result[j] = '\0'; // Null-terminate the result string
    lcd_command(0x01); // Clear the LCD
    _delay_ms(2);
    lcd_print(result); // Print the resulting letters
}

int main(void) {
    lcd_init(); // Initialize the LCD
    lcd_print("Press a key:"); // Print an initial message
    _delay_ms(1000);
      
    keypad_init();
    char key;
    char key_str[2]; // Array to hold the key as a string
   
    char key_store[20]; // Array to store the pressed keys (increased size)
    int count = 0; // Counter for stored keys
    char last_key = '\0'; // Variable to track the last key pressed

    while (1) {
        key = keypad_read(); // Read the key from the keypad
        if (key && key != last_key) { // Check if a key is pressed and it's different from the last key
            if (key != '*') {
                // Store the key if it's not '*'
                if (count < sizeof(key_store) - 1) { // Ensure we don't overflow the array
                    key_store[count] = key;
                    count++;
                }
            } else {
                // If '*' is pressed, convert and display the stored keys
                convert_to_letters(key_store, count);
                
                // Wait for a moment to see the output
                //_delay_ms(2000); // Wait for 2 seconds to see the output

                // Clear the key_store array
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
