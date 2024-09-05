#ifndef DATA_H
#define DATA_H

#include <unordered_map>
#include <string>
#include <mutex>
#include <chrono>
#include <thread>

class Data
{
public:
    static Data& getInstance();
    void storeKeyValue(const std::string& key, const std::string& value);
    std::string getValue(const std::string& key);
    bool deleteKey(const std::string& key);
    void deleteAllKeys();
    void setKeyExpiration(const std::string& key, int seconds);
    void checkExpiredKeys();
    std::unordered_map<std::string, std::string> getAllKeyValuePairs();

private:
    Data();
    std::unordered_map<std::string, std::string> dataMap;
    std::unordered_map<std::string, std::chrono::time_point<std::chrono::steady_clock>> expirationMap;
    std::mutex dataMutex;
};

#endif // DATA_H