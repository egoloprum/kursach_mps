#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"

char convert_to_letters(char* key_store, int count) {
  char last_char = '\0'; // Variable to hold the last generated character

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
      last_char = 'A' + (press_count - 1) % 3; // a, b, c
    } else if (key == '3') {
      last_char = 'D' + (press_count - 1) % 3; // d, e, f
    } else if (key == '4') {
      last_char = 'G' + (press_count - 1) % 3; // g, h, i
    } else if (key == '5') {
      last_char = 'J' + (press_count - 1) % 3; // j, k, l
    } else if (key == '6') {
      last_char = 'M' + (press_count - 1) % 3; // m, n, o
    } else if (key == '7') {
      last_char = 'P' + (press_count - 1) % 4; // p, q, r, s
    } else if (key == '8') {
      last_char = 'T' + (press_count - 1) % 3; // t, u, v
    } else if (key == '9') {
      last_char = 'W' + (press_count - 1) % 4; // w, x, y, z
    }
  }

  return last_char; // Return the last generated character
}

#define BUZZER_PIN PD7

void setup() {
    // Set PD7 as an output
    DDRD |= (1 << BUZZER_PIN);
}

void toggle_buzzer() {
    PORTD ^= (1 << BUZZER_PIN);
}

// start
int main(void) {
  setup();
   
  //while(1) {
  //  toggle_buzzer();
  //  _delay_ms(1000); // Wait for 1 second
  //}
   
  lcd_init(); // Initialize the LCD
  lcd_print("Input gos nomer: "); // Print an initial message
  _delay_ms(2000);

  lcd_command(0x01); // Clear the LCD
  _delay_ms(2);

  keypad_init();
  char gos_nomer[10] = {0}; // Array to hold the car number
  int len_gos_nomer = 0;

  char key;
  char last_key = '\0'; // Variable to track the last key pressed
  char key_store[10] = {0}; // Temporary key store
  int len_key_store = 0;


  // gos nomer loop
  while(1) {
    key = keypad_read(); // Read the key press

    // Check if a key is pressed and it's different from the last key
    if (key && key != last_key) {
      
      // Insert key into key_store
      if (key != '*' && key != '#') {
        if (len_key_store < sizeof(key_store) - 1) {
          key_store[len_key_store] = key; // Store the key
          len_key_store++;
        }
      }

      // Clear key_store
      else if (key == '#') {
        len_key_store = 0; // Reset the key store
      }
    // Submit to gos_nomer
      else {
        // Check if we can add to gos_nomer
        if (len_gos_nomer < sizeof(gos_nomer) - 1) {

          if (len_gos_nomer == 0 || len_gos_nomer == 4 || len_gos_nomer == 5) {
            char that_letter = convert_to_letters(key_store, len_key_store);
            gos_nomer[len_gos_nomer] = that_letter;
          }

          else {
            char that_number = key_store[0]; // Get the first character from key_store
            gos_nomer[len_gos_nomer] = that_number; // Add to gos_nomer		      
          }

          len_gos_nomer++; // Increment the length
          gos_nomer[len_gos_nomer] = '\0'; // Null-terminate the string
        }

        // Clear key_store
        len_key_store = 0;

        // Update the LCD
        lcd_command(0x01); 
        _delay_ms(2);
	
	      char buffer[3]; // Buffer to hold the string representation (2 digits + null terminator)
        sprintf(buffer, "%d", len_gos_nomer);
	
        lcd_print(gos_nomer); 
	
        if (buffer[0] == '9') {
          break;
        }
      }
    
      last_key = key; // Update last_key to the current key
    } else if (!key) {
      // Reset last_key when no key is pressed
      last_key = '\0';
    }
  }

  //////////////////// end of gos_nomer ////////////////////

  _delay_ms(2000);
  lcd_command(0x01);
  _delay_ms(2);
  
  lcd_print("Input mass without load: ");
  _delay_ms(2000);
  lcd_command(0x01);
  _delay_ms(2);
  
  char mass_without_load[6] = {0};
  len_key_store = 0;
  strcpy(key_store, "");
  
  // mass without load loop
  while (1) {
    key = keypad_read();

    if (key && key != last_key) {
      if (key != '*' && key != '#') {
        if (len_key_store < sizeof(key_store) - 1) {
          key_store[len_key_store] = key;
          len_key_store++;

          lcd_command(0x01);
          _delay_ms(2);
          lcd_print(key_store);
        }
      }
      else {
        memcpy(mass_without_load, key_store, len_key_store);
        mass_without_load[len_key_store] = '\0';

        lcd_command(0x01);
        _delay_ms(500);
        char print_str[50];
        sprintf(print_str, "mass without load = %s", mass_without_load);
        lcd_print(print_str);
        break;
      }

    last_key = key;
    } else if (!key) {
      last_key = '\0';
    }
  }

  //////////////////// end of mass without load ////////////////////
  
  _delay_ms(2000);
  lcd_command(0x01);
  _delay_ms(2);
  
  lcd_print("Input mass with load: ");
  _delay_ms(2000);
  lcd_command(0x01);
  _delay_ms(2);
  
  char mass_with_load[6] = {0};
  len_key_store = 0;

  int z = 0;
  for (z = 0; z < sizeof(key_store); z++) {
    key_store[z] = '\0'; // Set each element to null character
  }

  // mass with load loop
  while (1) {
    key = keypad_read();

    if (key && key != last_key) {
      if (key != '*' && key != '#') {
        if (len_key_store < sizeof(key_store) - 1) {
          key_store[len_key_store] = key;
          len_key_store++;

          lcd_command(0x01);
          _delay_ms(2);
          lcd_print(key_store);
        }
      }
      else {
        memcpy(mass_with_load, key_store, len_key_store);
        mass_with_load[len_key_store] = '\0'; 
        
        lcd_command(0x01);
        _delay_ms(500);
        char print_str[50];
        sprintf(print_str, "mass with load = %s", mass_with_load);
        lcd_print(print_str);
        break;
      }

    last_key = key;
    } else if (!key) {
      last_key = '\0';
    }
  }

  //////////////////// end of mass with load ////////////////////

  
}
