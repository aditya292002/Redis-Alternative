#include "Data.h"

Data& Data::getInstance()
{
    static Data instance;
    return instance;
}

void Data::storeKeyValue(const std::string& key, const std::string& value)
{
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[key] = value;
}

std::string Data::getValue(const std::string& key)
{
    std::lock_guard<std::mutex> lock(dataMutex);
    auto it = dataMap.find(key);
    if (it != dataMap.end()) {
        return it->second;
    }
    return "";
}