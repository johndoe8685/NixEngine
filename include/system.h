#pragma once
#include "directory.h"
#include "debugger.h"

class System
{
public:
	Debugger debugger;
	Directory directory;

	System(std::string className);
};