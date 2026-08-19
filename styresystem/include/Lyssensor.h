// Lyssensor.h
#ifndef LYSSENSOR_H
#define LYSSENSOR_H

#include <avr/io.h>
#include <stdint.h>


 
 
 
class Lyssensor
{
public:
    
    // adcChannel 0-15 svarer til A0-A15 p Arduino Mega 2560.
    
    explicit Lyssensor(uint8_t adcChannel);

    
    // Læser aktuelt lysniveau fra ADC'en.
    //return 10-bit værdi fra ADC (0-1023).
    
    uint16_t getLysSignal();
	
private:
    uint8_t channel;   // Hvilken ADC-kanal sensoren sidder på

    void initADC();    // Sætter ADC op (reference, prescaler osv.)
};

#endif
