#include "Data.h"

Data& Data::getInstance()
{
    static Data instance;
    return instance;
}

Data::Data()
{
    // Start a background thread to periodically check for expired keys
    std::thread([this]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            checkExpiredKeys();
        }
    }).detach();
}

void Data::storeKeyValue(const std::string& key, const std::string& value)
{
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[key] = value;
    expirationMap.erase(key); // Remove any existing expiration for this key
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

bool Data::deleteKey(const std::string& key)
{
    std::lock_guard<std::mutex> lock(dataMutex);
    expirationMap.erase(key);
    return dataMap.erase(key) > 0;
}

void Data::deleteAllKeys()
{
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap.clear();
    expirationMap.clear();
}

void Data::setKeyExpiration(const std::string& key, int seconds)
{
    std::lock_guard<std::mutex> lock(dataMutex);
    auto it = dataMap.find(key);
    if (it != dataMap.end()) {
        expirationMap[key] = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    }
}

void Data::checkExpiredKeys()
{
    std::lock_guard<std::mutex> lock(dataMutex);
    auto now = std::chrono::steady_clock::now();
    for (auto it = expirationMap.begin(); it != expirationMap.end(); ) {
        if (it->second <= now) {
            dataMap.erase(it->first);
            it = expirationMap.erase(it);
        } else {
            ++it;
        }
    }
}

std::unordered_map<std::string, std::string> Data::getAllKeyValuePairs()
{
    std::lock_guard<std::mutex> lock(dataMutex);
    return dataMap;
}