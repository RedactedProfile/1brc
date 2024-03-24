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


// Global debug level (set this to control output)
int GlobalDebugLevel = 3; // show all;

// open log file
std::ofstream DebugFile("log.txt", std::ios::out | std::ios::app);

#define _LOG(level, label, msg) do { \
    if ((level) <= GlobalDebugLevel) { \
        auto now = std::chrono::system_clock::now(); \
        auto now_c = std::chrono::system_clock::to_time_t(now); \
        auto timestamp = std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S"); \
        std::cout << timestamp << " | " << label << "(" << (level) << "): " << (msg) << std::endl; \
        DebugFile << timestamp << " | " << label << "(" << (level) << "): " << (msg) << std::endl; \
    } \
} while(0)


#define CRIT_LOG(mes) _LOG(0, "CRITICAL", mes);
#define ERR_LOG(mes) _LOG(1, "ERROR", mes);
#define DEB_LOG(mes) _LOG(2, "DEBUG", mes);
#define INF_LOG(mes) _LOG(3, "INFO", mes);


int main() {

    INF_LOG("INFO LOG TEST");
    DEB_LOG("DEBUG LOG TEST");
    ERR_LOG("ERROR LOG TEST");
    CRIT_LOG("CRITIAL ERROR LOG TEST");




    DebugFile.close();
    return 0;
}