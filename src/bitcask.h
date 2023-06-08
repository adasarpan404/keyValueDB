#ifndef BITCASK_H
#define BITCASK_H

#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
class Bitcask
{
public:
    Bitcask(const string &dataPath);

    bool Put(const string &key, const string &value);

    string Get(const string &key);

    bool Delete(const string &key);

    void SwitchToNextFile();

private:
    string dataPath_;
    int currentIndex_;
    unordered_map<string, streampos> index_;
    unordered_set<string> deletedKeys_;
};

#endif // BITCASK_H
