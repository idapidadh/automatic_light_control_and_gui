#include "SystemindstillingKontrol.h"
#include "Systemindstillinger.h"
#include <stdio.h>        // for snprintf
#include <avr/eeprom.h>   // AVR EEPROM-bibliotek

// Statisk buffer til at holde tekststreng med systemindstillinger.
// getSystemindstillinger() returnerer en pointer til denne.
static char systemindstillingerStr[32];

// EEPROM-adresser (n byte pr. vrdi)
static uint8_t* const EEPROM_ADDR_LYS = (uint8_t*)0;
static uint8_t* const EEPROM_ADDR_TID = (uint8_t*)1;

void SystemindstillingKontrol::initFraEEPROM()
{
	// Læs værdier (0255) fra EEPROM
	uint8_t lys = eeprom_read_byte(EEPROM_ADDR_LYS);	// Vrdier lst fra EEPROM kommer som uint8_t
	uint8_t tid = eeprom_read_byte(EEPROM_ADDR_TID);

	// Ugyldige vrdier -> fald tilbage til domneklassens defaults
	if (lys < 1 || lys > 100) {
		lys = Systemindstillinger::getLysintensitet();      // default 80
	}
	if (tid < 1 || tid > 120) {
		tid = Systemindstillinger::getTidsfoelsomhed();     // default 20
	}

	// Initialiserer domæneklassen med gyldige værdier
	Systemindstillinger::init(lys, tid);
}

// Private hjælpefunktioner til at gemme systemindstillinger i EEPROM
void SystemindstillingKontrol::gemLysI_EEPROM(int lys)
{
	eeprom_update_byte(EEPROM_ADDR_LYS, (uint8_t)lys);
}

void SystemindstillingKontrol::gemTidI_EEPROM(int tid)
{
	eeprom_update_byte(EEPROM_ADDR_TID, (uint8_t)tid);
}

const char* SystemindstillingKontrol::getSystemindstillinger()
{
	int lys = Systemindstillinger::getLysintensitet();
	int tid = Systemindstillinger::getTidsfoelsomhed();

	// Skriv fx "lys=70tid=20" ind i buffer
	snprintf(systemindstillingerStr,
	sizeof(systemindstillingerStr),
	"lys=%dtid=%d",
	lys,
	tid);

	return systemindstillingerStr;
}

// Set lysintensitet og tidsfølsomhed
bool SystemindstillingKontrol::setLysintensitet(int lysintensitet)
{
	bool anvendt = Systemindstillinger::setLysintensitet(lysintensitet);
	if (!anvendt) {
		return false;
	}

	// Gem i EEPROM hvis værdien er gyldig
	gemLysI_EEPROM(lysintensitet);
	return true;
}

bool SystemindstillingKontrol::setTidsfoelsomhed(int tidsfoelsomhed)
{
	bool anvendt = Systemindstillinger::setTidsfoelsomhed(tidsfoelsomhed);
	if (!anvendt) {
		return false;
	}

	gemTidI_EEPROM(tidsfoelsomhed);
	return true;
}