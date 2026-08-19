#pragma once
#include <stdint.h>

class Lyskilde
{
	public:
	// Konstruktor: sltter PWM op på Timer 3, OC3A (pin 5)
	Lyskilde();

	// Sat lysstyrke som duty cycle i procent (0-100).
	// Internt bliver værdien begrænset til max 80 %.
	void setLysPWM(double dutyCycle);

	private:
	
};

