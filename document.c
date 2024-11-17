#include <stdlib.h>
#include "document.h"

// Simple LCG for generating pseudo-random numbers
unsigned long lcg_random() {
    static unsigned long seed = 123456789; 			// Initial seed value
    seed = (1103515245 * seed + 12345) % (1UL << 31); 		// LCG formula
    return seed;
}

float random_float(float min, float max) {
    return min + (lcg_random() % (unsigned long)((max - min) * 100)) / 100.0f;
}

int random_int(int min, int max) {
    return min + (lcg_random() % (max - min + 1));
}

Document* document_initializer() {
    static Document doc[10];
   
    int i = 0;
    for (i = 0; i < 10; i++) {
        doc[i].mass_without_cargo = random_float(10.0f, 20.0f); 
        doc[i].mass_with_cargo = random_float(20.0f, 40.0f);     
        doc[i].number_of_items = random_int(3, 20);              
    }

    return doc;
}
