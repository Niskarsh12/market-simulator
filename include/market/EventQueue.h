#pragma once

#include <queue>
#include <vector>
#include "Event.h"

namespace market {

class EventQueue {
public:
    void push(const Event& e);
    Event pop();
    bool empty() const;

private:
    struct Compare {
        bool operator()(const Event& a, const Event& b) const {
            return a.time > b.time; // min-heap
        }
    };

    std::priority_queue<Event, std::vector<Event>, Compare> queue;
};

} // namespace market
