#include "debugger.h"

Debugger::Debugger(std::string className)
    :m_className(className)
{
}

void Debugger::giveMessage(DebugLevel level, std::string message)
{
    switch (level)
    {
    case Info:
        std::cout << "[INFO]  " << "[" << m_className << "]" << message << std::endl;
        break;
    case Warning:
        std::cout << "[WARN]  " << "[" << m_className << "]" << message << std::endl;
        break;
    case Error:
        std::cout << "[ERROR] " << "[" << m_className << "]" << message << std::endl;
        break;
    case Unknown:
        std::cout << "[UNKWN] " << "[" << m_className << "]" << message << std::endl;
        break;
    default:
        break;
    }
}

void Debugger::giveMessage(DebugLevel level, std::string funcName, std::string message)
{
    switch (level)
    {
    case Info:
        std::cout << "[INFO]  " << "[" << m_className << "::" << funcName << "> " << message << std::endl;
        break;
    case Warning:
        std::cout << "[WARN]  " << "[" << m_className << "::" << funcName << "> " << message << std::endl;
        break;
    case Error:
        std::cout << "[ERROR] " << "[" << m_className << "::" << funcName << "> " << message << std::endl;
        break;
    case Unknown:
        std::cout << "[UNKWN] " << "[" << m_className << "::" << funcName << "> " << message << std::endl;
        break;
    default:
        break;
    }
}
