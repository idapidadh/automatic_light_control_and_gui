#include "AutomatiskLyskontrol.h"
#include "Lyssensor.h"
#include "Lyskilde.h"
#include "Systemindstillinger.h"
#include "Bevaegelsessensor.h"

AutomatiskLyskontrol::AutomatiskLyskontrol(Lyssensor& lyssensor, Lyskilde& lyskilde)
: lyssensor_(lyssensor),
lyskilde_(lyskilde),
dutyCycle(0.0),
timerAktiv(false),
resterendeSekunder(0),
sekundTaeller(0),
trin_lysJustering(1),
forventetMaxLysSignal(1008),
forventetMinLysSignal(0)
{
}

void AutomatiskLyskontrol::startLys() {
	g_bevaegelse_set_flag = 0;
	startTimer();
}

void AutomatiskLyskontrol::startTimer() {
	int tidsfoelsomhed = Systemindstillinger::getTidsfoelsomhed();

	if (tidsfoelsomhed < 1)  tidsfoelsomhed = 1;
	if (tidsfoelsomhed > 120) tidsfoelsomhed = 120;
	
	resterendeSekunder = tidsfoelsomhed*60;
	timerAktiv         = true;
}

void AutomatiskLyskontrol::justerLysOpad() {
	dutyCycle += trin_lysJustering;
}

void AutomatiskLyskontrol::justerLysNedad() {
	if (dutyCycle > 0.0) {
		dutyCycle -= trin_lysJustering;
		if (dutyCycle < 0.0) { // Forhindrer ulogisk adfærd, hvis der sendes negativ PWM i setLysPWM()
			dutyCycle = 0.0;
		}
	}
}

void AutomatiskLyskontrol::slutLys() {
	timerAktiv         = false;
	dutyCycle          = 0.0;

	lyskilde_.setLysPWM(dutyCycle);
}

void AutomatiskLyskontrol::kontrollerLys() {

	if (g_bevaegelse_set_flag) {
		startLys();
	}

	sekundTaeller++;
	bool etSekundGaet = false;
	if (sekundTaeller >= 100) {
		sekundTaeller = 0;
		etSekundGaet = true;
	}

	if (timerAktiv) {
		if (etSekundGaet && resterendeSekunder > 0) {
			resterendeSekunder--;
			if (resterendeSekunder == 0) {
				slutLys();
				return;
			}
		}

		int lysSignalADC = lyssensor_.getLysSignal();
		// Skalering af lyssignal -> // giver værdi 0-100 som er sammenlignelig med lysintensitet
		int lysSignalSkaleret = (((lysSignalADC - forventetMinLysSignal) * 100UL) / (forventetMaxLysSignal - forventetMinLysSignal));
		
		
		int lysintensitet = Systemindstillinger::getLysintensitet();
		
		// Hysterese: beregner procentuel afvigelse
		int forskel = lysintensitet - lysSignalSkaleret;
		if (forskel < 0) {
			forskel = forskel*(-1);
		}
		double procentuelAfvigelse = ((double)forskel/(double)lysintensitet)*100; // typecasting undgår at vi runder ned til 0, inden vi får omsat til procent ved *100

		if (procentuelAfvigelse > 5) {
			if (lysSignalSkaleret < lysintensitet) {
				justerLysOpad();
				} else if (lysSignalSkaleret > lysintensitet) {
				if (dutyCycle > 0.0) {
					justerLysNedad();
				}
			}
		}

		lyskilde_.setLysPWM(dutyCycle);
	}
}
