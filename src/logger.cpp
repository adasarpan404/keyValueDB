#include "logger.h"
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

Logger::Logger() {
    logFilePath = "log.keyvalue";
    logEntries = vector<LogEntry>();
    logData = unordered_map<string, string>();
    currentId = 1;
}



string Logger::getCurrentTimestamp() {
    time_t now = time(nullptr);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(timestamp);
}

void Logger::readLogFromFile() {
    ifstream logFile(logFilePath);

    if (!logFile.is_open()) {
        cout << "Log file not found. Creating a new file.\n";
        ofstream newFile(logFilePath);  // Create a new file
        newFile.close();
        return;
    }

    string line;
    int highestId = 0;  // Initialize highestId to 0

    while (getline(logFile, line)) {
        istringstream iss(line);
        string idStr, timestamp, key, value;

        if (getline(iss, idStr, '|') && getline(iss, timestamp, '|') && getline(iss, key, ':') && getline(iss, value)) {
            int id = stoi(idStr);  // Convert idStr to integer

            LogEntry entry;
            entry.id = id;
            entry.timestamp = timestamp;
            entry.key = key;
            entry.value = value;
            logEntries.push_back(entry);
            logData[key] = value;

            if (id > highestId) {
                highestId = id;  // Update highestId if a higher ID is found
            }
        }
    }

    logFile.close();

    currentId = highestId + 1;  // Set currentId to the highest ID + 1

    cout << "Log file read successfully." << endl;

    // Display retrieved log entries
    cout << "Retrieved log entries:" << endl;
    for (const auto& entry : logEntries) {
        cout << entry.id << " | " << entry.timestamp << " | " << entry.key << " : " << entry.value << endl;
    }
}

void Logger::writeToLog(const string& key, const string& value) {
    LogEntry entry;
    entry.id = currentId++;
    entry.timestamp = getCurrentTimestamp();
    entry.key = key;
    entry.value = value;

    logEntries.push_back(entry);
    logData[key] = value;

    cout << "Entry written to log. ID: " << entry.id << ", Key: " << entry.key << ", Value: " << entry.value << endl;
}

void Logger::readAllEntries() {
    cout << "All log entries:" << endl;
    for (const auto& entry : logEntries) {
        cout << entry.id << " | " << entry.timestamp << " | " << entry.key << " : " << entry.value << endl;
    }
}

void Logger::readValueForKey(const string& key) {
    auto it = logData.find(key);
    if (it != logData.end()) {
        cout << "Value for key '" << key << "': " << it->second << endl;
    } else {
        cout << "Key not found." << endl;
    }
}

void Logger::readValueForId(int id) {
    bool found = false;
    for (const auto& entry : logEntries) {
        if (entry.id == id) {
            cout << "Entry for ID " << id << ":" << endl;
            cout << entry.id << " | " << entry.timestamp << " | " << entry.key << " : " << entry.value << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "ID not found." << endl;
    }
}

void Logger::saveLogToFile() {
    ofstream logFile(logFilePath);

    if (!logFile.is_open()) {
        cout << "Error: Failed to open log file for writing.\n";
        return;
    }

    for (const auto& entry : logEntries) {
        logFile << entry.id << "|" << entry.timestamp << "|" << entry.key << ":" << entry.value << "\n";
    }

    logFile.close();

    cout << "Log file saved successfully." << endl;
}
