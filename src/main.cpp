#include <iostream>
#include "market/Simulator.h"

using namespace market;

int main() {
    Simulator sim;

    sim.schedule(Event(5.0, EventType::OrderArrival, 1));
    sim.schedule(Event(1.0, EventType::Trade, 2));
    sim.schedule(Event(3.0, EventType::AgentAction, 3));

    sim.run();

    return 0;
}
