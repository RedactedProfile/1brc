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
#include <filesystem>
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

    INF_LOG("Kyle's 1brc - attempt 1 - the 'dumb' approach");
    INF_LOG("=============================================");

    DEB_LOG("Loading input..");
    
    std::string filename = "measurements.txt";
    if (!std::filesystem::exists(filename)) {
        CRIT_LOG("File doesn't exist");
        exit(1);
    }

    std::ifstream file(filename);

    // Phase 1: Read the data from file
    int line_num = 0;
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line)) {
            //parser(line, line_num);
            
            INF_LOG(line);
            for (int i = 0; i < line.size(); i++) {

            }
            
            line_num++;
        }
    }

    file.close();

    DebugFile.close();
    return 0;
}