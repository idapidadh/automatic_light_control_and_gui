#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "GUIkommunikation.h"
#include "Systemindstillinger.h"
#include "SystemindstillingKontrol.h"
#include "Lyssensor.h"
#include "Bevaegelsessensor.h"
#include "Lyskilde.h"
#include "AutomatiskLyskontrol.h"

// Objekter
Lyssensor lyssensor(1);
Lyskilde  lyskilde;
AutomatiskLyskontrol kontrol(lyssensor, lyskilde);
// -----------------------------------------------------------------

int main() {
	cli();  // Stopper alle interrupts globalt imens der initieres

	// Domæne- og GUI-init
	SystemindstillingKontrol::initFraEEPROM();
	GUIkommunikation::init(9600);

	// Bevægelsessensor + automatisk lyskontrol
	init_bevaegelsessensor();
	kontrol.slutLys();           // Forhindrer lyskilde i at lyse ganske svagt

	// 30 sekunders kalibrering til bevægelsessensoren. Fjernet.
	//_delay_ms(30000);

	sei(); // Enabler global interrupt igen

	char kommando[RX_BUFFER_SIZE];

	while (1) {

		// ---------- Automatisk Lyskontrol ----------
		kontrol.kontrollerLys();
		// -------------------------------------------

		// ---------- GUI-kommunikation ----------
		if (GUIkommunikation::harFejl()) {
			GUIkommunikation::sendString("fejl\n");
			GUIkommunikation::clearFejl();
		}

		if (GUIkommunikation::linjeKlar()) {
			GUIkommunikation::hentLinje(kommando, sizeof(kommando));

			if (strcmp(kommando, "systemindstillinger") == 0) {
				const char* systemindstillingerStr =
				SystemindstillingKontrol::getSystemindstillinger();
				GUIkommunikation::sendString(systemindstillingerStr);
				GUIkommunikation::sendString("\n");

				} else if (strncmp(kommando, "lys=", 4) == 0) {
				int lysintensitet = atoi(kommando + 4);
				bool anvendt = SystemindstillingKontrol::setLysintensitet(lysintensitet);
				GUIkommunikation::sendString(anvendt ? "anvendt\n" : "fejl\n");

				} else if (strncmp(kommando, "tid=", 4) == 0) {
				int tidsfoelsomhed = atoi(kommando + 4);
				bool anvendt = SystemindstillingKontrol::setTidsfoelsomhed(tidsfoelsomhed);
				GUIkommunikation::sendString(anvendt ? "anvendt\n" : "fejl\n");

				} else {
				GUIkommunikation::sendString("fejl\n");
			}
		}
		// ---------------------------------------

		_delay_ms(10);   // ca. 100 kontrollerLys() pr. sekund til timer
	}

	return 0;
}
