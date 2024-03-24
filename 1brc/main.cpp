#define _CRT_SECURE_NO_WARNINGS
///
/// In this implementation, we're going in "dumb" and assuming nothing about anything except that it's a big file
/// 

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "execution_timer.hpp"
#include "string_tools.hpp"


// Global debug level (set this to control output)
int GlobalDebugLevel = 3; // show all;

// open log file
std::ofstream DebugFile("log.txt", std::ios::out | std::ios::app);

#define _DLOG(level, label, msg) do { \
    if ((level) <= GlobalDebugLevel) { \
        auto now = std::chrono::system_clock::now(); \
        auto now_c = std::chrono::system_clock::to_time_t(now); \
        auto timestamp = std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S"); \
        std::cout << timestamp << " | " << label << "(" << (level) << "): " << (msg) << std::endl; \
        DebugFile << timestamp << " | " << label << "(" << (level) << "): " << (msg) << std::endl; \
    } \
} while(0)

#define CRIT_LOG(mes) _DLOG(0, "CRITICAL", mes);
#define ERR_LOG(mes) _DLOG(1, "ERROR", mes);
#define DEB_LOG(mes) _DLOG(2, "DEBUG", mes);
#define INF_LOG(mes) _DLOG(3, "INFO", mes);

#define LOG(mes) std::cout << mes << std::endl;

int main() {
    ExecutionTimer<std::chrono::milliseconds> timer;

    LOG("Welcome");




    DebugFile.close();
    return 0;
}