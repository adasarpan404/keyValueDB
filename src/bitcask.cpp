#include "bitcask.h"
#include <fstream>
#include <sstream>

using namespace std;
Bitcask::Bitcask(const string &dataPath)
    : dataPath_(dataPath), currentIndex_(0) {}

bool Bitcask::Put(const string &key, const string &value)
{
    ofstream dataFile(dataPath_ + to_string(currentIndex_) + ".data", ios::app);
    if (!dataFile)
        return false;

    ofstream indexFile(dataPath_ + to_string(currentIndex_) + ".index", ios::app);
    if (!indexFile)
        return false;

    streampos offset = dataFile.tellp();
    index_[key] = offset;
    indexFile << key << ' ' << offset << ' ' << value.length() << '\n';
    dataFile << value << '\n';

    dataFile.close();
    indexFile.close();

    return true;
}

string Bitcask::Get(const string& key) {
    if (deletedKeys_.count(key) > 0)
        return "";  // Key is deleted (tombstone)

    if (index_.find(key) == index_.end())
        return "";  // Key not found

    ifstream indexFile(dataPath_ + to_string(currentIndex_) + ".index");
    if (!indexFile)
        return "";  // Unable to open index file

    string line;
    while (getline(indexFile, line)) {
        istringstream iss(line);
        string storedKey;
        string offsetStr;
        size_t length;
        if (iss >> storedKey >> offsetStr >> length && storedKey == key) {
            if (length == 0) {
                indexFile.close();
                return "";  // Tombstone marker
            }

            ifstream dataFile(dataPath_ + to_string(currentIndex_) + ".data");
            if (!dataFile)
                return "";  // Unable to open data file

            streampos offset = stoll(offsetStr);
            dataFile.seekg(offset);

            string value;
            value.resize(length);
            dataFile.read(&value[0], length);

            dataFile.close();
            indexFile.close();

            return value;
        }
    }

    indexFile.close();

    return "";  // Key not found
}


bool Bitcask::Delete(const string &key)
{
    if (index_.find(key) == index_.end())
        return false;

    ofstream indexFile(dataPath_ + to_string(currentIndex_) + ".index", ios::app);

    if (!indexFile)
        return false;
    indexFile << key << ' ' << 0 << ' ' << 0 << '\n';

    indexFile.close();
    return true;
}

void Bitcask::SwitchToNextFile()
{
    currentIndex_++;
}
