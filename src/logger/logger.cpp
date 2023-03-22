#include "logger.h"

Logger::Logger(): output(std::ofstream("wolfenstein_like.log")) {}

Logger& Logger::log() {
    static Logger logger;
    return logger;
}

void Logger::write(std::string msg) {
    log().output << msg << std::endl;
}
