#pragma once
#include <iostream>
#include <string>


using namespace std;

class Trade {
    public:
        double p;
        double v;
        double q;
        size_t t;
        bool is_buyer_maker;

        Trade(double p, double v, double q, size_t t, bool is_buyer_maker);
};

ostream& operator<<(ostream& os, const Trade& trade);

// TradeReader is used to read trades from a binary file using mmap 
// The file is assumed to be sorted by timestamp
// // using mmap in a way that always offset is 0


class TradeReader {
    public:
        string symbol;
        size_t count; // Number of trades in binary file
        void* mmap_file;
        size_t record_size;

    public:
        TradeReader(string symbol);
        ~TradeReader();
        Trade * first();
        Trade * last();
};
