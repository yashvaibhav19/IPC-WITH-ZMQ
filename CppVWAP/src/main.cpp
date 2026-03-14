#include <cstdio>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include "log.hpp"
#include "ConfigReader.hpp"
#include "Consumer.hpp"

void InitLogger()
{
    std::filesystem::create_directories("LOGS");
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_r(&t, &tm);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d%m%Y");
    std::string filename = "LOGS/log_" + oss.str() + ".log"; // Format DDMMYYYY
    FILE* log_fd = std::fopen(filename.c_str(), "a");
    if (log_fd)
        Output2FILE::Stream() = log_fd;
#ifdef DEBUG
    FILELog::ReportingLevel() = logDEBUG4;
#else
    FILELog::ReportingLevel() = logINFO;
#endif
}

int main()
{
    InitLogger();
    ConfigReader::getInstance().readConfig();
    L_(logINFO) << "CppVWAP started";
    
    Consumer *tradeConsumer = new Consumer(ConfigReader::getInstance().getConfigValue("zmq-addr"), 
                                            std::stoi(ConfigReader::getInstance().getConfigValue("zmq-hwm"))) ;
    tradeConsumer->start_consuming();

    sleep(100000000);
    return 0;
}