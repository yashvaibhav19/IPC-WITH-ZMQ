#include "Consumer.hpp"

void Consumer::process_trade(const json& data) {
#ifdef DEBUG
    L_(logDEBUG4) << "Data Received In process_trade(): " << data.dump();
    L_(logDEBUG4) << data["t"] << " " << data["p"] << " " << data["v"] ;
#endif
    auto res = symbolToVWAP.GetSignal(data["s"],ExchData{data["t"],data["p"],data["v"]});
    switch(res)
    {
        case Signal::BUY: {
            L_(logINFO) << "BUY order for";
            OrderGateway::Send(data["s"]);
            break;
        }
        case Signal::SELL: {
            L_(logINFO) << "SELL order for";
            OrderGateway::Send(data["s"]);
            break;
        }
        default: {
#ifdef DEBUG
            L_(logINFO) << "No action required";
#endif
        }
    }
}

void Consumer::start_consuming() {
    auto lambda = [&](){
        zmq::message_t message;
        
        while (true) {
            auto result = subscriber.recv(message, zmq::recv_flags::none);
            
            if (result) {
                try {
                    std::string msg_str(static_cast<char*>(message.data()), message.size());
                    json trade_data = json::parse(msg_str);
                    
                    process_trade(trade_data);
                } catch (const json::parse_error& e) {
                    L_(logERROR) << "JSON Parse Error: " << std::string(e.what());
                }
            }
        }
    };

    std::thread consumer_thread(lambda);
    pthread_t hp = consumer_thread.native_handle();

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(std::stoi(ConfigReader::getInstance().getConfigValue("consumer-thread-affinity")), &cpuset);

    int status = pthread_setaffinity_np(hp, sizeof(cpu_set_t), &cpuset);
    if (status != 0) {
        L_(logERROR) << "Error setting thread affinity for core " << ConfigReader::getInstance().getConfigValue("consumer-thread-affinity");
    } else {
        L_(logINFO) << "Consumer thread successfully pinned to CPU core " << ConfigReader::getInstance().getConfigValue("consumer-thread-affinity");
    }
    consumer_thread.detach();
}