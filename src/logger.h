#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
struct LogEntry {
    string key;
    string value;
    string timestamp;
};

class Logger {
public:
    void writeToLog(const string& key, const string& value);
    void saveLogToFile();
    void readLogFromFile();
    void readAllEntries();
    void readValueForKey(const string& key);

private:
    vector<LogEntry> logEntries;
    unordered_map<string, string> logData;

    string getCurrentTimestamp();
};

#endif  // LOGGER_H
