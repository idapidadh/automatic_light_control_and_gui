#include "GUIkommunikation.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h> // strncpy

#define F_CPU 16000000UL

// Globale volatile variabler -> Compiler SKAL lse fra RAM hver gang, fordi ISR-rutine og main ndrer i dem
volatile char    g_rxBuffer[RX_BUFFER_SIZE]; // Buffer til besked
volatile uint8_t g_rxIndeks      = 0;        // Hvor langt vi er net i buffer
volatile bool    g_linjeKlar     = false;    // der ligger en komplet linje i g_rxBuffer
volatile bool    g_paritetsfejl  = false;    // flag for paritetsfejl
volatile bool    g_overflowFejl  = false;    // flag for buffer-overflow

ISR(USART0_RX_vect) {
	uint8_t status = UCSR0A;
	char c = UDR0;

	if (status & _BV(UPE0)) {
		g_paritetsfejl = true;
		return;
	}

	if (c == '\n') {
		g_rxBuffer[g_rxIndeks] = '\0';
		g_rxIndeks = 0;
		g_linjeKlar = true;
		} else {
		if (g_rxIndeks < RX_BUFFER_SIZE - 1) {
			g_rxBuffer[g_rxIndeks] = c;
			g_rxIndeks++;
			} else {
			g_rxIndeks = 0;
			g_overflowFejl = true;
		}
	}
}

void GUIkommunikation::init(int baudrate) {
	UCSR0A = 0; // Statusflag nulstilles for en sikkerheds skyld

	int ubrr = F_CPU / (16UL * baudrate) - 1;
	UBRR0H = static_cast<uint8_t>(ubrr >> 8);
	UBRR0L = static_cast<uint8_t>(ubrr);

	UCSR0B = _BV(TXEN0) | _BV(RXEN0) | _BV(RXCIE0); // transmitter enable, receiver enable, receiver interrupt enable
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00) | _BV(UPM01); // 8E1
}

void GUIkommunikation::sendChar(char c) {
	while (!(UCSR0A & _BV(UDRE0))) {}
	UDR0 = c;
}

void GUIkommunikation::sendString(const char* s) {
	while (*s != '\0') {
		sendChar(*s++);
	}
}

bool GUIkommunikation::linjeKlar() {
	return g_linjeKlar;
}

bool GUIkommunikation::harFejl() {
	return g_paritetsfejl || g_overflowFejl;
}

void GUIkommunikation::clearFejl() {
	g_paritetsfejl = false;
	g_overflowFejl = false;
}

void GUIkommunikation::hentLinje(char* kommando, int kommandoSize) {
	cli(); // Disable global interrupt imens vi kopierer
	strncpy(kommando, (const char*)g_rxBuffer, kommandoSize);
	kommando[kommandoSize - 1] = '\0';
	g_linjeKlar = false;
	sei(); // Enable global interrupt
}