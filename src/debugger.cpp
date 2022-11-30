#include "debugger.h"

Debugger::Debugger(std::string componentName, std::string className)
    :m_componentName(componentName), m_className(className)
{
}

Debugger::Debugger(std::string className)
    :m_componentName("Unknown"), m_className(className)
{
}

void Debugger::giveMessage(DebugLevel level, std::string message)
{
    if (message != m_previousMessage)
    {
        m_previousMessage = message;
        switch (level)
        {
        case Info:
            std::cout << "[INFO]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << m_className << "> " << message << std::endl;
            break;
        case Warning:
            std::cout << "[WARN]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << m_className << "> " << message << std::endl;
            break;
        case Error:
            std::cout << "[ERROR] " << "[" << m_componentName << "::" << m_className << "] " << "[" << m_className << "> " << message << std::endl;
            break;
        case Unknown:
            std::cout << "[UNKWN] " << "[" << m_componentName << "::" << m_className << "] " << "[" << m_className << "> " << message << std::endl;
            break;
        default:
            break;
        }
    }
}

void Debugger::giveMessage(DebugLevel level, std::string funcName, std::string message)
{
    if (message != m_previousMessage)
    {
        m_previousMessage = message;
        switch (level)
        {
        case Info:
            std::cout << "[INFO]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << funcName << "> " << message << std::endl;
            break;
        case Warning:
            std::cout << "[WARN]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << funcName << "> " << message << std::endl;
            break;
        case Error:
            std::cout << "[ERROR] " << "[" << m_componentName << "::" << m_className << "] " << "[" << funcName << "> " << message << std::endl;
            break;
        case Unknown:
            std::cout << "[UNKWN] " << "[" << m_componentName << "::" << m_className << "] " << "[" << funcName << "> " << message << std::endl;
            break;
        default:
            break;
        }
    }
}
