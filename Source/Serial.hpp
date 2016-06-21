#pragma once

#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

extern std::string arduinoBuffer;

class Serial
{
	private:
		const char* portName;
		HANDLE hSerial;
		bool connected;
		COMSTAT status;
		DWORD errors;

	public:
		Serial(const char *portName);
		~Serial();
		std::string getPortName();
		int ReadData(char *buffer, unsigned int nbChar);
		std::string readData();
		bool WriteData(char *buffer, unsigned int nbChar);
		bool IsConnected();
};