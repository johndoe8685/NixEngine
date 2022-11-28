#pragma once
#include <iostream>
#include "window.h"
class Debugger
{
private:
	std::string m_className;
public:
	enum DebugLevel
	{
		Info,
		Warning,
		Error,
		Unknown
	};
	Debugger(std::string className);
	
	void giveMessage(DebugLevel level, std::string message);
	void giveMessage(DebugLevel level, std::string funcName, std::string message);
};