#pragma once

#include <iostream>

#include "Singleton.h"

class Logger : public Singleton<Logger>
{
    friend class Singleton<Logger>;

public:
    enum Prio: unsigned int
    {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };

    template <typename... Targs>
    bool line(int priority, std::string format, Targs... args)
    {
        if (this->log(priority, format, args...))
        {
            std::cerr << std::endl;
            return true;
        }

        return false;
    }
    template <typename... Targs>
    bool line(std::string format, Targs... args)
    {
        return this->line(0, format, args...);
    }

    template <typename... Targs>
    bool log(int priority, std::string format, Targs... args)
    {
        if (this->isEnabled() && this->checkPriority(priority))
        {
            this->printf(format.c_str(), args...);
            return true;
        }

        return false;
    }
    template <typename... Targs>
    bool log(std::string format, Targs... args)
    {
        return this->log(0, format, args...);
    }

    void setPriority(int priority);
    bool checkPriority(int priority);

    bool isEnabled() const;
    void enable();
    void disable();

protected:
    Logger();

private:
    void printf(const char* format);

    template<typename T, typename... Targs>
    void printf(const char* format, T value, Targs... args)
    {
        for (; *format != '\0'; format++)
        {
            if (*format == '%')
            {
                std::cerr << value;
                printf(format + 1, args...);
                return;
            }
            std::cerr << *format;
        }
    }

    int priority = 0;
    bool enabled = true;
};
