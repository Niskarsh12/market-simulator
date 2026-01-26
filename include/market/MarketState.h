#pragma once

#include <vector>
namespace market {

struct MarketState {
    std::vector<double> bids;
    std::vector<double> asks;
    double last_price = 0.0;

};

}
