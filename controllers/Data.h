#ifndef DATA_H
#define DATA_H

#include <unordered_map>
#include <string>
#include <mutex>

class Data
{
public:
    static Data& getInstance();
    void storeKeyValue(const std::string& key, const std::string& value);
    std::string getValue(const std::string& key);

private:
    Data() = default;
    std::unordered_map<std::string, std::string> dataMap;
    std::mutex dataMutex;
};

#endif // DATA_H