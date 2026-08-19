#include "Lyskilde.h"
#include <avr/io.h>

#define MAX_DUTY_PERCENT 80.0   // HARDWARE-BESKYTTELSE: MAX 80 %
#define TIMER3_TOP        249   // Giver ~1 kHz ved 16 MHz og prescaler 64

// Konstruktor: initialiserer Timer 3 til Fast PWM på OC3A (pin 5)
// Sørger for at alt bliver sat rigtigt op
Lyskilde::Lyskilde()
{
	// OC3A ligger på PE3. sæt PE3 som output
	DDRE |= (1 << DDE3); //PORTE bit 3 -> den fysiske pin hvor OCR3 er hardware output hvor PWM bliver styret
	//Bliver sat til output

	// Nulstil timerkontrolregistre
	TCCR3A = 0;
	TCCR3B = 0;

	// Fast PWM, mode 14: WGM33:0 = 1110
	TCCR3A |= (1 << WGM31);
	TCCR3B |= (1 << WGM33) | (1 << WGM32);

	// Non-inverting mode p? OC3A (clear on compare match, set at BOTTOM)
	TCCR3A |= (1 << COM3A1);

	// Sæt TOP-værdi
	ICR3 = TIMER3_TOP;

	// Prescaler
	TCCR3B |= (1 << CS31) | (1 << CS30);
}

// Sætter duty cycle (0-100), men begrænser til max 80 %
void Lyskilde::setLysPWM(double dutyCycle)
{
	// 1) Begræns til [0; MAX_DUTY_PERCENT]
	if (dutyCycle < 0.0)
	dutyCycle = 0.0;

	if (dutyCycle > MAX_DUTY_PERCENT)
	dutyCycle = MAX_DUTY_PERCENT;
	
	// SLUK HELT
	if (dutyCycle == 0.0) {
		// Frakobl OC3A fra PWM
		TCCR3A &= ~((1 << COM3A1) | (1 << COM3A0));

		// Sæt pin PE3 lav
		PORTE &= ~(1 << PORTE3);

		OCR3A = 0;
		return;
	}
	
	// TND PWM igen
	// Genskab non-inverting PWM mode
	TCCR3A |= (1 << COM3A1);
	TCCR3A &= ~(1 << COM3A0);
	
	// 2) Regn duty (%) om til OCR3A-værdi
	//    duty = OCR3A / ICR3 * 100  ?  OCR3A = duty * ICR3 / 100
	double ratio = dutyCycle / 100.0;
	uint16_t ocr_val = (uint16_t)(ratio * (double)TIMER3_TOP + 0.5); // afrunder

	// 3) Skriv til compare-registeret. styrer PWM-udgangen på pin 5
	OCR3A = ocr_val;
}
