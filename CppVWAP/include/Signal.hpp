#ifndef __SIGNAL_VWAP_FINNHUB_HPP__
#define __SIGNAL_VWAP_FINNHUB_HPP__

#include<unordered_map>
#include<map>
#include<deque>
#include<cstdint>
#include "OrderGateway.hpp"
#include "StructDefinitions.hpp"

class VWAP {
    std::deque<ContiguousData> dq;
    const uint64_t windowSize = 15 * (60'000); // 15 minute for ms precision data being consumed
public:
    VWAP() = default;
    Signal Insert(const ExchData&& data);
};

class SymbolToVWAP {
    std::unordered_map<std::string,VWAP> symbol_vwap_map;

public:
    Signal GetSignal(const std::string& , const ExchData&& data);

};
#endif /* __SIGNAL_VWAP_FINNHUB_HPP__*/