#include <iostream>
#include "market/EventQueue.h"

using namespace market;

int main() {
    EventQueue eq;

    eq.push(Event(5.0, EventType::OrderArrival, 1));
    eq.push(Event(1.0, EventType::Trade, 2));
    eq.push(Event(3.0, EventType::AgentAction, 3));

    while (!eq.empty()) {
        Event e = eq.pop();
        std::cout << "Event id=" << e.id
                  << " time=" << e.time << "\n";
    }

    return 0;
}
