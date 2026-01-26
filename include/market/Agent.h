#pragma once

#include "Event.h"
#include "MarketState.h"


namespace market {
    class Agent {
        public: 
           virtual ~Agent() = default;

           // Agent decides what to do at a given time
           virtual Event act(double time, const MarketState& state) = 0;
    };
}