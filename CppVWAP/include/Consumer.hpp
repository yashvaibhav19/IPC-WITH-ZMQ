#ifndef __CONSUMER_ZMQ_CPPVWAP__
#define __CONSUMER_ZMQ_CPPVWAP__

#include <zmq.hpp>
#include <thread>
#include <pthread.h>
#include "json.hpp"
#include "log.hpp"
#include "ConfigReader.hpp"
#include "Signal.hpp"

using json = nlohmann::json;

class Consumer {
public:
    Consumer(const std::string& addr, int hwm) 
        : address(addr), 
          context(1), 
          subscriber(context, zmq::socket_type::sub) {
        subscriber.set(zmq::sockopt::rcvhwm, hwm);
        subscriber.connect(address);
        subscriber.set(zmq::sockopt::subscribe, "");
        
        L_(logINFO) << "Consumer connected to " << address << " with HWM " << hwm;
    }

    void start_consuming();

private:
    void process_trade(const json& data);

    std::string address;
    zmq::context_t context;
    zmq::socket_t subscriber;

    SymbolToVWAP symbolToVWAP;
};

#endif /* __CONSUMER_ZMQ_CPPVWAP__ */