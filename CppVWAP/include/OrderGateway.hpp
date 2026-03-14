#ifndef __ORDER_GATEWAY_MOCK_ENGINE__
#define __ORDER_GATEWAY_MOCK_ENGINE__

#include "log.hpp"

class OrderGateway {
public:
    static void Send(const std::string&);
};

#endif /* __ORDER_GATEWAY_MOCK_ENGINE__ */