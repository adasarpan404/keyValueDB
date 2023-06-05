#include <iostream>
#include <string>
#include <sstream>
#include "log.h"

int main() {
    std::string input;

    Log log("log.customext");

    std::cout << "Welcome to the Log Shell! Enter 'help' for a list of commands or 'q' to quit." << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "q") {
            break;
        } else if (input == "help") {
            std::cout << "Available commands:" << std::endl;
            std::cout << "- key-get: Get the value associated with a key." << std::endl;
            std::cout << "- key-get all: Get all values without timestamps." << std::endl;
            std::cout << "- key-write value: Write a new key-value pair to the log." << std::endl;
            std::cout << "- help: Display this help message." << std::endl;
            std::cout << "- q: Quit the program." << std::endl;
        } else {
            std::stringstream ss(input);
            std::string command;
            std::string key;
            std::string value;

            ss >> command >> key;

            if (command == "key-get") {
                if (key == "all") {
                    log.PrintLogWithoutTimestamp();
                } else {
                    std::string value = log.GetLogValueByKey(key);
                    if (value.empty()) {
                        std::cout << "No matching entry found for key: " << key << std::endl;
                    } else {
                        std::cout << "Value: " << value << std::endl;
                    }
                }
            } else if (command == "key-write") {
                ss >> value;
                if (value.empty()) {
                    std::cout << "Invalid command. Usage: key-write value" << std::endl;
                } else {
                    log.WriteToLog(key, value);
                    std::cout << "Log entry added successfully." << std::endl;
                }
            } else {
                std::cout << "Invalid command. Enter 'help' for a list of commands." << std::endl;
            }
        }
    }

    return 0;
}
