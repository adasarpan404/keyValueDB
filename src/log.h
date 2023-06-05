#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>

class Log {
public:
    Log(const std::string& fileName);
    void WriteToLog(const std::string& key, const std::string& value);
    void PrintLog();
    void PrintLogWithoutTimestamp();
    std::string GetLogValueByKey(const std::string& key);

private:
    std::ofstream logFile;
};

#endif
