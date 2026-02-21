#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace Utils {

std::mutex Logger::s_mutex;

static std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%H:%M:%S");
    return ss.str();
}

void Logger::info(const std::string& message) {
    std::lock_guard<std::mutex> lock(s_mutex);
    std::cout << "[" << getTimestamp() << "] [INFO] " << message << std::endl;
}

void Logger::warning(const std::string& message) {
    std::lock_guard<std::mutex> lock(s_mutex);
    std::cout << "[" << getTimestamp() << "] [WARN] " << message << std::endl;
}

void Logger::error(const std::string& message) {
    std::lock_guard<std::mutex> lock(s_mutex);
    std::cerr << "[" << getTimestamp() << "] [ERROR] " << message << std::endl;
}

} // namespace Utils
