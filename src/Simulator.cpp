#include "market/Simulator.h"
#include <iostream>

namespace market {

Simulator::Simulator()
    : current_time(0.0) {}

void Simulator::schedule(const Event& e) {
    event_queue.push(e);
}

void Simulator::run() {
    while (!event_queue.empty()) {
        Event e = event_queue.pop();

        // advance time
        current_time = e.time;

        // process event (for now, just print)
        std::cout << "[time=" << current_time
                  << "] processing event id=" << e.id
                  << "\n";
    }
}

} // namespace market
