#include "OrderGateway.hpp"

void OrderGateway::Send(const std::string& symbol)
{
    L_(logINFO) << "Mock Order booked for Symbol: "<< symbol;
}