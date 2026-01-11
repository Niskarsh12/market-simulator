#pragma once

#include "EventQueue.h"

namespace market {

class Simulator {
public:
    Simulator();

    void schedule(const Event& e);
    void run();

private:
    double current_time;
    EventQueue event_queue;
};

} // namespace market
