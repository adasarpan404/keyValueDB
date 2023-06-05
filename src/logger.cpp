#include "logger.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <sstream>

using namespace std;
void Logger::writeToLog(const string& key, const string& value) {
    string timestamp = getCurrentTimestamp();

    LogEntry entry;
    entry.key = key;
    entry.value = value;
    entry.timestamp = timestamp;

    logEntries.push_back(entry);
    logData[key] = value;

    cout << "Log entry added successfully." << endl;
}

void Logger::saveLogToFile() {
    ofstream logFile;
    logFile.open("log.keyvalue");

    if (!logFile.is_open()) {
        cout << "Failed to open log file." << endl;
        return;
    }

    for (const auto& entry : logEntries) {
        logFile << entry.timestamp << " | " << entry.key << " : " << entry.value << endl;
    }

    logFile.close();

    cout << "Log file saved successfully." << endl;
}

void Logger::readLogFromFile() {
    ifstream logFile;
    logFile.open("log.keyvalue");

    if (!logFile.is_open()) {
        cout << "Failed to open log file." << endl;
        return;
    }

    string line;
    while (getline(logFile, line)) {
        istringstream iss(line);
        string timestamp, key, value;
        if (getline(iss, timestamp, '|') && getline(iss, key, ':') && getline(iss, value)) {
            LogEntry entry;
            entry.timestamp = timestamp;
            entry.key = key;
            entry.value = value;
            logEntries.push_back(entry);
            logData[key] = value;
        }
    }

    logFile.close();

    cout << "Log file read successfully." << endl;

    // Display retrieved log entries
    cout << "Retrieved log entries:" << endl;
    for (const auto& entry : logEntries) {
        cout << entry.timestamp << " | " << entry.key << " : " << entry.value << endl;
    }
}

string Logger::getCurrentTimestamp() {
    time_t now = time(nullptr);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(timestamp);
}

void Logger::readAllEntries() {
    cout << "All key-value entries:\n";
    for (const auto& entry : logEntries) {
        cout << entry.timestamp << " - Key: " << entry.key << ", Value: " << entry.value << "\n";
    }
}

void Logger::readValueForKey(const string& key) {
    bool found = false;
    for (const auto& entry : logEntries) {
        if (entry.key == key) {
            cout << "Value for key '" << key << "': " << entry.value << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No value found for key '" << key << "'.\n";
    }
}
