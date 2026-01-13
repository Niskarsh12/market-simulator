#pragma once

#include "EventQueue.h"
#include "Event.h"
#include "MarketState.h"

namespace market {

class Simulator {
public:
    Simulator();

    void schedule(const Event& e);
    void run();

private:
    double current_time;
    EventQueue event_queue;
    MarketState state;

    // 👇 THESE TWO WERE MISSING
    void handle_event(const Event& e);
    void print_state(const Event& e) const;
};

}
