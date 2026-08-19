

#include "Bevaegelsessensor.h"   
#include <avr/io.h>
#include <avr/interrupt.h>

// Globale Variabler
volatile uint8_t g_bevaegelse_set_flag = 0; 

// INITIALISERING
extern "C" {
    
    void init_bevaegelsessensor(void) {
        // Sæt Pin 2 (PE4) til INPUT
        DDRE &= ~(1 << DDE4); 
        
        // Aktivér intern pull-up modstand
        PORTE |= (1 << PORTE4);
        
        // Konfigurer INT4 til RISING EDGE (ISC41=1, ISC40=1)
        EICRB |= (1 << ISC41) | (1 << ISC40); 
        
        // Aktivér External Interrupt 4 (INT4)
        EIMSK |= (1 << INT4); 
    }
} 

// INTERRUPT SERVICE ROUTINE

extern "C" { 
    //Bevægelse registreret
    ISR(INT4_vect) { 
        // Sæt flag for at signalere bevægelse til Kontrol-klassen
        g_bevaegelse_set_flag = 1; 
    }
}