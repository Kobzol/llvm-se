#include "Logger.h"

Logger::Logger()
{

}

void Logger::printf(const char* format)
{
    std::cerr << format;
}

bool Logger::isEnabled() const
{
    return this->enabled;
}
void Logger::enable()
{
    this->enabled = true;
}
void Logger::disable()
{
    this->enabled = false;
}

void Logger::setPriority(int priority)
{
    this->priority = priority;
}

bool Logger::checkPriority(int priority)
{
    return priority >= this->priority;
}
