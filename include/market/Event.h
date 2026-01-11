#pragma once

#include <cstdint>

namespace market {

enum class EventType {
    OrderArrival,
    Trade,
    AgentAction
};

struct Event {
    double time;        // simulation time
    EventType type;     // what kind of event
    uint64_t id;        // unique id (for debugging)

    Event(double t, EventType tp, uint64_t i)
        : time(t), type(tp), id(i) {}
};

} // namespace market
