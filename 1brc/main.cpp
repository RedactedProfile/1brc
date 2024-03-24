#define _CRT_SECURE_NO_WARNINGS
///
/// In this implementation, we're going in "dumb" and assuming nothing about anything except that it's a big file
/// 

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <unordered_map>
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

typedef struct datum_s {
    std::string label;
    float value;
} datum_t;
/// <summary>
/// Converts a string of ; deliminated values into a specifically typed pair pair 
/// </summary>
datum_t station_split(std::string line, char split_at = ';') {
    std::istringstream iss(line);
    datum_t out;
    bool left = true;
    std::string token;
    while (std::getline(iss, token, split_at)) {
        if (left) out.label = token;
        else out.value = std::stof(token);
        left = false;
    }

    return out;
}




#define STATION_PREALLOCATION 200
std::unordered_map<std::string, uint32_t> stations;
std::vector<std::ifstream> fileHandlers = {};

uint32_t file_id = 0;
uint32_t createFileHandler() {

}
void getFileHandler() {

}



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
            
            //INF_LOG(line);

            // So for this approach, we can try using the string tools to split at ; into a pair, i imagine this isn't the most efficient usage but it's simple and to the point
            datum_t datum = station_split(line);

            // note: there's now 40 million approaches we could take here to organize the data discovered. Which is the nature of this challenge. 
            // - we could do it enitrely in memory, build up an unordered map with the station as the key and then for each station we can analyze the values
            //   but I have doubts the upper limit of usual memory capacity would make this not a viable solution
            //   we could instead write the values to binary data files, separated by station, using the filesystem as a sort of on-the-fly database

            // yeah let's do that

            // strayegy here is this: 
            //     Because the station names use non ASCII charcaters, we can't create filenames based sqaurely on the name, not in a way that's reconstructable anyways
            //     So we'll create map of file pointers, the filenames will simply be "1.dat", "2.dat" but we'll map a station name like "St. Lucas's" to it's associated dat file. 
            //     The "dat" file will contain nothing but a sequential list of floats.  
            //     This map could simply be a vector of strings (station names) and the index can be the file pointer




            if (stations.find(datum.label) == stations.end()) {
                DEB_LOG("entry doesn't exist for this label, creating it");
                stations[datum.label] = createFileHandler();
            }

            // getFileHandler(datum.value);
            
            
            line_num++;
        }
    }

    file.close();

    DebugFile.close();
    return 0;
}