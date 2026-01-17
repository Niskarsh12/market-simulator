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
    void log_state();


private:
    double current_time;
    EventQueue event_queue;
    MarketState state;
    std::ofstream log_file;
    // 👇 THESE TWO WERE MISSING
    void handle_event(const Event& e);
    void print_state(const Event& e) const;
};




}


