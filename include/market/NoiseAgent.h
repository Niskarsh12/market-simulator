#pragma once

#include "market/Agent.h"
#include "market/Event.h"
#include "market/MarketState.h"

#include <random>

namespace market {

class NoiseAgent : public Agent {
public:
    explicit NoiseAgent(int id);

    Event act(double current_time, const MarketState& state) override;

private:
    int agent_id;

    std::mt19937 rng;
    std::uniform_real_distribution<double> price_dist;
    std::uniform_int_distribution<int> side_dist;
    std::uniform_real_distribution<double> time_dist;
};

}
