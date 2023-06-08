#include "bitcask.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main()
{
    Bitcask db("./data/");
    string command;
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
            cout << "put <key> <value>\n";
            cout << "get <key>\n";
            cout << "next\n";
            cout << "exit\n";
        }
        else if (cmd == "put")
        {
            string key, value;
            iss >> key >> value;
            if (db.Put(key, value))
                cout << "OK\n";
            else
                cout << "Error\n";
        }
        else if (cmd == "get")
        {
            string key;
            iss >> key;
            string value = db.Get(key);
            if (value != "")
                cout << value << '\n';
            else
                cout << "Not found\n";
        }
        else if (cmd == "delete")
        {
            string key;
            iss >> key;
            if (db.Delete(key))
                cout << "OK\n";
            else
                cout << "Error\n";
        }
        else if (cmd == "next")
        {
            db.SwitchToNextFile();
            cout << "OK\n";
        }
        else if (cmd == "exit")
        {
            break;
        }
        else
        {
            cout << "Unknown command\n";
        }
    }

    return 0;
}
