#include <iostream>
#include "market/Simulator.h"

using namespace market;

int main() {
    Simulator sim;

    sim.schedule(Event(1.0, EventType::OrderArrival, Side::Buy, 100, 1, 1));
    sim.schedule(Event(2.0, EventType::OrderArrival, Side::Sell, 105, 1, 2));
    sim.schedule(Event(3.0, EventType::OrderArrival, Side::Buy, 106, 1, 3));

    sim.run();
}


    

