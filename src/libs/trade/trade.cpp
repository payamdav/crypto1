#include "trade.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include "../core/config/config.hpp"
#include "../utils/file_utils.hpp"


using namespace std;

Trade::Trade(double p, double v, double q, size_t t, bool is_buyer_maker) {
    this->p = p;
    this->v = v;
    this->q = q;
    this->t = t;
    this->is_buyer_maker = is_buyer_maker;
}

ostream& operator<<(ostream& os, const Trade& trade) {
    os << "Trade: " << trade.p << " " << trade.v << " " << trade.q << " " << trade.t << " " << trade.is_buyer_maker;
    return os;
}

TradeReader::TradeReader(string symbol) {
    this->symbol = symbol;
    string file_path = Config::getInstance().data_path + "/" + symbol + ".trades";
    this->record_size = sizeof(Trade);
    this->count = utils::get_file_size(file_path) / this->record_size;
    
    int fd = open(file_path.c_str(), O_RDONLY);
    this->mmap_file = mmap(NULL, this->count * this->record_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
}

TradeReader::~TradeReader() {
    munmap(this->mmap_file, this->count * this->record_size);
}

Trade * TradeReader::first() {
    return (Trade *)this->mmap_file;
}

Trade * TradeReader::last() {
    return (Trade *)this->mmap_file + this->count - 1;
}

