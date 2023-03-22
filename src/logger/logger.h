#pragma once

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

class Logger {
    Logger();
    std::ofstream output;

public:
    static Logger& log();
    static void write(std::string msg);
};

template<class T>
Logger& operator<<(Logger& log, const T& msg) {
    log << msg;
    return log;
}
