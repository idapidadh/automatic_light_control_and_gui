#pragma once

#include <stdint.h>      // uint16_t

// Forward declarations
// fordi vi kun holder REFERENCER til dem.
class Lyssensor;
class Lyskilde;

class AutomatiskLyskontrol {
	public:
	AutomatiskLyskontrol(Lyssensor& lyssensor, Lyskilde& lyskilde);

	void kontrollerLys();

	void startLys();
	void startTimer();
	void justerLysOpad();
	void justerLysNedad();
	void slutLys();

	private:
	Lyssensor& lyssensor_;
	Lyskilde&  lyskilde_;

	double   dutyCycle;
	bool     timerAktiv;
	int resterendeSekunder;
	int sekundTaeller;

	int trin_lysJustering;
	int forventetMaxLysSignal;
	int forventetMinLysSignal;
};
