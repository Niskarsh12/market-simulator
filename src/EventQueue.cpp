#include "market/EventQueue.h"

namespace market {

void EventQueue::push(const Event& e) {
    queue.push(e);
}

Event EventQueue::pop() {
    Event e = queue.top();
    queue.pop();
    return e;
}

bool EventQueue::empty() const {
    return queue.empty();
}

} // namespace market
