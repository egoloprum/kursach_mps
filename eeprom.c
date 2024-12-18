#include "eeprom.h"

// Define the Truck array (this should match the `extern` declaration in the header)
struct Truck trucks[5] = {
    {"A123BC077", "1000", "1500"},
    {"B456DE088", "2000", "2500"},
    {"P777PP777", "3000", "3500"},
    {"C789FG099", "4000", "4500"},
    {"D012GH000", "5000", "5500"}  
};

struct Truck read_trucks[5] = {};

// Function to write a truck to EEPROM
void write_truck_to_eeprom(uint16_t addr, struct Truck* truck) {
    int i = 0;
    for (i = 0; i < 9; i++) {
        eeprom_write_byte((uint8_t*) (addr + i), truck->gos_nomer[i]);
    }

    for (i = 0; i < 4; i++) {
        eeprom_write_byte((uint8_t*) (addr + 9 + i), truck->mass_without_load[i]);
    }

    for (i = 0; i < 4; i++) {
        eeprom_write_byte((uint8_t*) (addr + 13 + i), truck->mass_with_load[i]);
    }
}

// Function to write all trucks to EEPROM
void write_all_trucks_to_eeprom(void) {
    int i = 0;
    for (i = 0; i < 5; i++) {
        write_truck_to_eeprom(i * (17), &trucks[i]);
    }
}

// Function to read a truck from EEPROM
void read_truck_from_eeprom(uint16_t addr, struct Truck* truck) {
    int i = 0;
    for (i = 0; i < 9; i++) {
         char data = eeprom_read_byte((uint8_t*) (i + addr));
         truck->gos_nomer[i] = data;
    }
    truck->gos_nomer[10] = '\0';  

    for (i = 0; i < 4; i++) {
        char data = eeprom_read_byte((uint8_t*) (i + addr + 9));
        truck->mass_without_load[i] = data;
    }
    truck->mass_without_load[5] = '\0';  

    for (i = 0; i < 4; i++) {
        char data = eeprom_read_byte((uint8_t*) (i + addr + 13));
        truck->mass_with_load[i] = data;
    }
    truck->mass_with_load[5] = '\0'; 
}

// Function to read all trucks from EEPROM
void read_all_trucks_from_eeprom(void) {
    int i = 0;
    for (i = 0; i < 5; i++) {
        read_truck_from_eeprom(i * (17), &read_trucks[i]);
    }
}
