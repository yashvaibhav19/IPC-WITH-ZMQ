#ifndef FKJD8_KJSF8_KJFS87
#define FKJD8_KJSF8_KJFS87

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

#include "log.hpp"

class ConfigReader {
private:
    ConfigReader() {}

    ConfigReader(const ConfigReader&) = delete;
    ConfigReader& operator=(const ConfigReader&) = delete;

    std::unordered_map<std::string,std::string> keyValue;
public:
    static ConfigReader& getInstance() {
        static ConfigReader instance;
        return instance;
    }

    void readConfig() {
        std::string configFilePath = "CONFIG/config.txt";
        std::ifstream file(configFilePath);
        if (!file.is_open()) {
            L_(logERROR) << configFilePath <<" is missing. Exiting...";
            exit(EXIT_FAILURE);
        }
        std::string temp;
        while(getline(file,temp))
        {
            if(temp.size()<2) continue;
            std::string key = "", value = "";
            size_t flag = 0;
            while(flag<temp.size() && temp[flag]!='=')
                key+=temp[flag++];
            flag++;
            while(flag<temp.size() && temp[flag]!='=')
                value+=temp[flag++];
            keyValue[key]=value;
        }
        L_(logINFO) << "Config file reading complete.";
    }

    std::string getConfigValue(std::string query)
    {
        auto itr = keyValue.find(query);
        if(itr == keyValue.end())
            return "";
        return itr->second;
    }
};

#endif /* FKJD8_KJSF8_KJFS87 */