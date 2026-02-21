#pragma once

#include <string>
#include <mutex>

namespace Utils {

class Logger {
public:
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);

private:
    static std::mutex s_mutex;
};

} // namespace Utils
