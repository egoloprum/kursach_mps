#ifndef DOCUMENT_H
#define DOCUMENT_H

typedef struct {
    char* plate_number;
    float mass_without_cargo; 	// Mass without cargo in kilograms
    float mass_with_cargo;     	// Mass with cargo in kilograms
    int   number_of_items;      // Number of items in cargo spaces
} Document;

Document* document_initializer();

#endif // DOCUMENT_H
