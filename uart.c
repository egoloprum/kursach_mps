#define F_CPU 8000000UL  // 8 MHz clock frequency
#include <avr/io.h>
#include <util/delay.h>
#include "eeprom.h"

void uart_init(unsigned int baud) {
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    UBRRH = (unsigned char)(ubrr >> 8);  // Set baud rate (high byte)
    UBRRL = (unsigned char)ubrr;        // Set baud rate (low byte)
    UCSRB = (1 << TXEN) | (1 << RXEN);  // Enable transmitter and receiver
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);  // 8 data bits, 1 stop bit
}

void uart_transmit(char data) {
    while (!(UCSRA & (1 << UDRE)));  // Wait for the transmit buffer to be empty
    UDR = data;                      // Send data
}

void uart_transmit_string(const char* str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

int main(void) {
    uart_init(9600);  // Initialize UART with 9600 baud rate

   write_all_trucks_to_eeprom();
   read_all_trucks_from_eeprom();
   
  int i = 0;
  for (i = 0; i < 5; i++) {

        uart_transmit_string(read_trucks[i].gos_nomer);
        uart_transmit_string("\r\n");
     
        uart_transmit_string(read_trucks[i].mass_without_load);
        uart_transmit_string("\r\n");
     
        uart_transmit_string(read_trucks[i].mass_with_load);
        uart_transmit_string("\r\n");
	
        _delay_ms(1000);  // Wait 1 second
  }
}
