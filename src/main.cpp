#include <iostream>
#include <string>
#include <sstream>
#include "logger.h"

using namespace std;
int main()
{
    Logger logger;
    string command;

    logger.readLogFromFile(); // Read data from log file at startup
    
    cout << "Interactive Log Shell\n";
    cout << "Type 'help' for available commands.\n";

    while (true)
    {
        cout << "> ";
        getline(cin, command);

        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "help")
        {
            cout << "Available commands:\n";
            cout << "  key-write <key> <value> : Write a key-value entry\n";
            cout << "  key-read all : Read all key-value entries\n";
            cout << "  key-read <key> : Read the value for a specific key\n";
            cout << "  save : Save log entries to file\n";
            cout << "  exit : Quit the program\n";
        }
        else if (cmd == "key-write")
        {
            string key, value;
            iss >> key >> value;
            logger.writeToLog(key, value);
        }
        else if (cmd == "key-read")
        {
            string subcommand;
            iss >> subcommand;

            if (subcommand == "all")
            {
                logger.readAllEntries();
            }
            else if(subcommand == "key"){
                string key;
                iss >> key;
                logger.readValueForKey(key);
            }else if(subcommand == "ID")
            {
                int ID;
                iss >> ID;
                logger.readValueForId(ID);
            }
        }
        else if (cmd == "save")
        {
            logger.saveLogToFile();
        }
        else if (cmd == "exit")
        {
            logger.saveLogToFile(); // Save log entries to file before exiting
            break;
        }
        else
        {
            cout << "Invalid command. Type 'help' for available commands.\n";
        }
    }

    return 0;
}
