#ifndef EEPROM_H
#define EEPROM_H

#include <avr/io.h>
#include <avr/eeprom.h>
#include <string.h>

// Define the Truck structure
struct Truck {
    char gos_nomer[9];         // License plate number (9 characters)
    char mass_without_load[4]; // Mass without load (as string)
    char mass_with_load[4];    // Mass with load (as string)
};

// Declare an array of 10 trucks
extern struct Truck trucks[5];

// Function to write a truck to EEPROM
void write_truck_to_eeprom(uint16_t addr, struct Truck* truck);

// Function to write all trucks to EEPROM
void write_all_trucks_to_eeprom(void);

// Function to read a truck from EEPROM
void read_truck_from_eeprom(uint16_t addr, struct Truck* truck);

// Function to read all trucks from EEPROM
void read_all_trucks_from_eeprom(void);

#endif // EEPROM_H
