#pragma once

#pragma once

#include "EventQueue.h"
#include "Event.h"
#include "MarketState.h"

#include <fstream>

namespace market {

class Simulator {
public:
    Simulator();
    ~Simulator();

    void schedule(const Event& e);
    void run();

    // random market activity
    void generate_random_orders(int count);

private:
    double current_time;
    EventQueue event_queue;
    MarketState state;

    std::ofstream log_file;

    void handle_event(const Event& e);
    void print_state(const Event& e) const;
    void log_state();
};

} // namespace market



