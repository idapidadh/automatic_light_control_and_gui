#pragma once

class SystemindstillingKontrol {
	public:
	// Kaldes ved opstart for at hente vrdier fra EEPROM
	static void initFraEEPROM();
	
	// Returnerer en C-streng med systemindstillingerne,
	// fx "lys=50tid=5"
	static const char* getSystemindstillinger();

	// Forsger at sætte ny lysintensitet.
	// Returnerer true hvis det er en gyldig værdi, ellers false.
	static bool setLysintensitet(int lysintensitet);

	// Forsøger at stte ny tidsflsomhed.
	// Returnerer true hvis det er en gyldig værdi, ellers false.
	static bool setTidsfoelsomhed(int tidsfoelsomhed);
	
	private:
	// Hjælpefunktioner til EEPROM
	static void gemLysI_EEPROM(int lys);
	static void gemTidI_EEPROM(int tid);
	
};