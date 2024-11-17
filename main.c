#include <avr/io.h>
#include <util/delay.h>

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"
#include "keypad.h"

const char* convert_to_letters(char* key_store, int count) {
    char* result = (char*)malloc(20 * sizeof(char)); 	// Allocate memory for the result
    if (result == NULL) {
        return NULL; 					// Check for allocation failure
    }

    int j = 0; 						// Index for the result array
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

    result[j] = '\0'; 			// Null-terminate the result string
    return result; 			// Return the dynamically allocated string
}

// checks if string has same chars
int areAllCharactersSame(const char *str) {
   if (str == NULL || str[0] == '\0') {
     return 1; 					// Consider empty string as having all same characters
   }

   char firstChar = str[0];
   int i = 1;
   for (i = 1; str[i] != '\0'; i++) {
     if (str[i] != firstChar) {
	 return 0; 				// Found a different character
     }
   }

   return 1; 					// All characters are the same
}

char* addChar(char* str, char ch) {
   int len = strlen(str);
   char* new_str = (char*)malloc(len + 2);
   if (new_str == NULL) {
      return NULL;
   }
   strcpy(new_str, str);
   new_str[len] = ch;
   new_str[len + 1] = '\0';
   free(str);

   return new_str; 
}

int main(void) {
   lcd_init(); 					// Initialize the LCD
   lcd_print("Press a key: "); 			// Print an initial message

   _delay_ms(2000);
   _delay_ms(2);

   keypad_init();
   char key;
   char key_store[20];
   int count = 0;

   char current_keys[10];
   int current_count = 0;

   int same_chars = -1;

   while (1) {
      key = keypad_read();

      if (key) {
	 // for writing current_keys
	 if (key != '*' && key != '#') {
	    if (current_count < sizeof(current_keys) - 1) { // Prevent overflow
	       current_keys[current_count] = key;
	       current_count++;
	    }
	    same_chars = areAllCharactersSame(current_keys);
	 }

	 // for clearing current_keys
	 else if (key == '#') {
	    lcd_command(0x01); 
	    _delay_ms(2);
	    strcpy(current_keys, "");
	    current_count = 0;
	 }

	 // for submitting it to key_store
	 else {
	    const char* add_key = convert_to_letters(current_keys, current_count);
	    if (add_key != NULL) {
	       if (count < sizeof(key_store) / sizeof(key_store[0])) { // Ensure space in key_store
		  strcpy(key_store[count], add_key); // Copy the string
		  count++;
	       }
	       free((void*)add_key); // Free the allocated memory
	    }
	    
	    lcd_command(0x01);
	    _delay_ms(2);
	    
	    lcd_print(current_keys);
	    _delay_ms(2);

	    strcpy(current_keys, "");
	    current_count = 0;
	 }

	 if (same_chars == 0) {
	    strcpy(current_keys, "");
	    current_count = 0;
	    lcd_command(0x01);
	    _delay_ms(2);
	    
	    lcd_print("Press the same keys then * please.");
	    _delay_ms(2000);
	    
	    lcd_command(0x01);
	    _delay_ms(2);
	 }
      }
   }

}
