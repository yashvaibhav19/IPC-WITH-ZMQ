#ifndef __STRUCT_DEFINITIONS_FINNHUB__
#define __STRUCT_DEFINITIONS_FINNHUB__

#include<cstdint>

struct ExchData {
    uint64_t timestamp;
    double price;
    double vol;
};
struct ContiguousData{
    uint64_t timestamp;
    double priceVolSum;
    double volSum;

    ContiguousData operator=(const ContiguousData& cd)
    {
        return ContiguousData{timestamp,priceVolSum,volSum};
    }
};

enum class Signal {
    PASS,
    BUY,
    SELL
};


#endif /* __STRUCT_DEFINITIONS_FINNHUB__ */