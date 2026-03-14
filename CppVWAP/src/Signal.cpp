#include "Signal.hpp"

Signal VWAP::Insert(const ExchData&& data)
{
    ContiguousData lastPop({0,0,0});
    while (!dq.empty() && (data.timestamp - dq.front().timestamp > windowSize)) {
        lastPop = dq.front();
        dq.pop_front();
    }
    dq.push_back({data.timestamp,(data.price)*(data.vol) + (dq.size()>0? dq.back().priceVolSum : 0),
                    data.vol+(dq.size()>0? dq.back().volSum:0)});
    double currentVWAP = (dq.back().priceVolSum - lastPop.priceVolSum)/(dq.back().volSum - lastPop.volSum);

    const double offMargin = 0.005; // for safety 
    if(currentVWAP * (1-offMargin) > data.price)
    {
        return Signal::BUY;
    }
    else if (currentVWAP * (1+ offMargin) < data.price)
    {
        return Signal::SELL;
    }
    return Signal::PASS;
}

Signal SymbolToVWAP::GetSignal(const std::string& symbol, const ExchData&& data)
{
    auto symbol_vwap_itr = symbol_vwap_map.find(symbol);
    if(symbol_vwap_itr == symbol_vwap_map.end()) [[unlikely]]
    {
        L_(logERROR) << "First exchange data for symbol " << symbol << " received.";
        return symbol_vwap_map[symbol].Insert(std::move(data));
    }
    auto& vwap = symbol_vwap_itr->second;
    return vwap.Insert(std::move(data));
}