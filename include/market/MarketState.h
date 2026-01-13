#pragma once

namespace market {

struct MarketState {
    double best_bid;
    double best_ask;
    double last_price;

    MarketState()
        : best_bid(0.0),
          best_ask(0.0),
          last_price(0.0) {}
};

}
