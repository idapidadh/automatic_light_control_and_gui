#include "Systemindstillinger.h"

// Default-vrdier (bruges hvis EEPROM er tom/ugyldig)
int Systemindstillinger::lysintensitet  = 80;
int Systemindstillinger::tidsfoelsomhed = 20;

void Systemindstillinger::init(int lys, int tid) {
	
	lysintensitet  = lys;
	tidsfoelsomhed = tid;
}

int Systemindstillinger::getLysintensitet() {
	return lysintensitet;
}

int Systemindstillinger::getTidsfoelsomhed() {
	return tidsfoelsomhed;
}

bool Systemindstillinger::setLysintensitet(int nyLysintensitet) {
	if (nyLysintensitet < 1 || nyLysintensitet > 100) {
		return false;
	}
	lysintensitet = nyLysintensitet;
	return true;
}

bool Systemindstillinger::setTidsfoelsomhed(int nyTidsfoelsomhed) {
	if (nyTidsfoelsomhed < 1 || nyTidsfoelsomhed > 120) {
		return false;
	}
	tidsfoelsomhed = nyTidsfoelsomhed;
	return true;
}
