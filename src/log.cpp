#include "log.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

Log::Log(const std::string& fileName) {
    logFile.open(fileName, std::ios_base::app);
    if (!logFile.is_open()) {
        std::cout << "Error opening log file." << std::endl;
    }
}

void Log::WriteToLog(const std::string& key, const std::string& value) {
    if (logFile.is_open()) {
        std::time_t currentTime = std::time(nullptr);
        std::string timeStamp = std::ctime(&currentTime);
        timeStamp.erase(timeStamp.find('\n'));

        logFile << "[" << timeStamp << "] " << "Key: " << key << " Value: " << value << std::endl;
    }
    else {
        std::cout << "Error opening log file." << std::endl;
    }
}

void Log::PrintLog() {
    logFile.close();

    std::ifstream inputFile("log.arpan");
    std::string line;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
        }

        inputFile.close();
    }
    else {
        std::cout << "Error opening log file for reading." << std::endl;
    }

    logFile.open("log.arpan", std::ios_base::app);
}

void Log::PrintLogWithoutTimestamp() {
    logFile.close();

    std::ifstream inputFile("log.arpan");
    std::string line;
    std::vector<std::string> keyValuePairs;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            size_t keyPos = line.find("Key: ");
            size_t valuePos = line.find("Value: ");
            if (keyPos != std::string::npos && valuePos != std::string::npos) {
                std::string key = line.substr(keyPos + 5, valuePos - keyPos - 6);
                std::string value = line.substr(valuePos + 7);
                keyValuePairs.push_back(key + ":" + value);
            }
        }

        inputFile.close();
    }
    else {
        std::cout << "Error opening log file for reading." << std::endl;
    }

    logFile.open("log.arpan", std::ios_base::app);

    std::cout << "[";
    for (size_t i = 0; i < keyValuePairs.size(); ++i) {
        std::cout << "{" << keyValuePairs[i] << "}";
        if (i < keyValuePairs.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

std::string Log::GetLogValueByKey(const std::string& key) {
    logFile.close();

    std::ifstream inputFile("log.arpan");
    std::string line;
    std::string value;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            if (line.find("Key: " + key) != std::string::npos) {
                size_t valuePos = line.find("Value: ");
                if (valuePos != std::string::npos) {
                    value = line.substr(valuePos + 7);
                    break;
                }
            }
        }

        inputFile.close();
    }
    else {
        std::cout << "Error opening log file for reading." << std::endl;
    }

    logFile.open("log.arpan", std::ios_base::app);

    return value;
}
