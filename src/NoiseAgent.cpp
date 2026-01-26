#include "market/NoiseAgent.h"

#include <random>

namespace market {

NoiseAgent::NoiseAgent(int id)
    : agent_id(id),
      rng(std::random_device{}()),
      price_dist(95.0, 105.0),
      side_dist(0, 1),
      time_dist(0.1, 1.0) {}

Event NoiseAgent::act(double current_time, const MarketState&) {
    double event_time = current_time + time_dist(rng);
    Side order_side = side_dist(rng) == 0 ? Side::Buy : Side::Sell;
    double order_price = price_dist(rng);
    int order_quantity = 100; // Default order quantity
    
    Event e(event_time, EventType::OrderArrival, order_side, 
            order_price, order_quantity, agent_id);
    return e;
}

} // namespace market

