#pragma once

#include <string>

class ErrorHandler
{
	private:
	public:
		static void Load(unsigned int errorCode, std::string fileName, std::string className, std::string functionName, std::string message);
		static void Raise(unsigned int errorCode);
};