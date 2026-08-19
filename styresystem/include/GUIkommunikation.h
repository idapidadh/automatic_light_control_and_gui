#pragma once
#include <stdint.h>

#define RX_BUFFER_SIZE 25 // buffer-størrelse til modtagne kommandoer

class GUIkommunikation {
	public:
	static void init(int baudrate);
	static void sendChar(char c);
	static void sendString(const char* s);

	static bool linjeKlar();
	static bool harFejl();
	static void clearFejl();
	static void hentLinje(char* kommando, int kommandoSize);
};