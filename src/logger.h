#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
struct LogEntry {
    int id;
    string timestamp;
    string key;
    string value;
};

class Logger {
private:
    string logFilePath;
    vector<LogEntry> logEntries;
    unordered_map<string, string> logData;
    int currentId;

    string getCurrentTimestamp();

public:
    Logger();
    void readLogFromFile();
    void writeToLog(const string& key, const string& value);
    void readAllEntries();
    void readValueForKey(const string& key);
    void saveLogToFile();
    void readValueForId(int id);
};

#endif  // LOGGER_H
