#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h" // Include the header file for function prototypes

#define KEYPAD_PORT PORTC
#define KEYPAD_DDR DDRC
#define KEYPAD_PIN PINC

// Function to initialize the keypad
void keypad_init() {
    KEYPAD_DDR = 0x0F; // Set PC0-PC3 as output (columns), PC4-PC6 as input (rows)
    KEYPAD_PORT = 0xF0; // Enable pull-up resistors on PC4-PC6
}

// Function to read the keypad
char keypad_read() {
    uint8_t row, col; // Declare loop variables outside the loop

    for (row = 0; row < 4; row++) {
        KEYPAD_PORT = ~(1 << row); // Set one column low at a time
        
        // Delay to stabilize the signal
        _delay_ms(10);
        
        // Check each row
        for (col = 0; col < 3; col++) {
            if (!(KEYPAD_PIN & (1 << (col + 4)))) { // Check if row is low
                // Debounce
                _delay_ms(10);
                if (!(KEYPAD_PIN & (1 << (col + 4)))) {
                    // Return the key pressed based on the row and column
                    // Map rows and columns to actual numbers
                    switch (row) {
                        case 0: // First row
                            switch (col) {
                                case 0: return '1'; // Row 0, Col 0
                                case 1: return '2'; // Row 0, Col 1
                                case 2: return '3'; // Row 0, Col 2
                            }
                            break;
                        case 1: // Second row
                            switch (col) {
                                case 0: return '4'; // Row 1, Col 0
                                case 1: return '5'; // Row 1, Col 1
                                case 2: return '6'; // Row 1, Col 2
                            }
                            break;
                        case 2: // Third row
                            switch (col) {
                                case 0: return '7'; // Row 2, Col 0
                                case 1: return '8'; // Row 2, Col 1
                                case 2: return '9'; // Row 2, Col 2
                            }
                            break;
                        case 3: // Third row
                            switch (col) {
                                case 0: return '*'; // Row 2, Col 0
                                case 1: return '0'; // Row 2, Col 1
                                case 2: return '#'; // Row 2, Col 2
                            }
                            break;
                    }
                }
            }
        }
    }
    return 0; // No key pressed
}
