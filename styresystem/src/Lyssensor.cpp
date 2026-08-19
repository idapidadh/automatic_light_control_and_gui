// Lyssensor.cpp
#include "Lyssensor.h"
#include <avr/io.h>

Lyssensor::Lyssensor(uint8_t adcChannel)
: channel(adcChannel)
{
	initADC();
}

void Lyssensor::initADC()
{
	// Brug AVcc som reference (5V) med kondensator p AREF
	// REFS1 = 0, REFS0 = 1
	ADMUX = (1 << REFS0);

	// Prescaler 128: 16 MHz / 128 = 125 kHz (inden for anbefalet område)
	// ADEN: enable ADC
	ADCSRA = (1 << ADEN) |
	(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	// Ingen auto trigger, ingen interrupts
	ADCSRB = 0x00;
}

uint16_t Lyssensor::getLysSignal()
{
	// Vælg kanal (0-15) til ATmega2560
	if (channel > 7)
	{
		ADCSRB |= (1 << MUX5);
	}
	else
	{
		ADCSRB &= ~(1 << MUX5);
	}

	// Nedre 3 bits i ADMUX vlger kanal 0-7
	uint8_t muxBits = channel & 0x07;
	ADMUX = (ADMUX & 0xF0) | muxBits;  // bevar referencebits (REFS0)

	// Start konvertering
	ADCSRA |= (1 << ADSC);

	// Vent til konvertering er frdig
	while (ADCSRA & (1 << ADSC))
	{
		// polling
	}

	// Ls 10-bit resultat
	uint16_t result = ADC;

	return result; // 0-1023
}
