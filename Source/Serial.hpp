#pragma once

#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Triggers.hpp"

extern std::string arduinoBuffer;

class Serial
{
	private:
		const char* portName;
		HANDLE hSerial;
		bool connected;
		COMSTAT status;
		DWORD errors;

		char charSerialBuffer[4096] = "";
		int dataLength = 4096;
		std::string serialBuffer;
		std::string currentSerialBuffer;
		int serialBufferSignal = 0;
		TriggerGroup* serialTriggers;

	public:
		Serial(const char *portName);
		~Serial();
		std::string getPortName();
		int ReadData(char *buffer, unsigned int nbChar);
		std::string readData();
		bool WriteData(char *buffer, unsigned int nbChar);
		bool IsConnected();
		void handleTriggers();
};