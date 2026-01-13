#pragma once

namespace market {

enum class EventType {
    OrderArrival,
    Trade
};

enum class Side {
    Buy,
    Sell
};

struct Event {
    double time;
    EventType type;
    Side side;
    double price;
    int quantity;
    int id;

    Event(double t, EventType ty, Side s,
          double p, int q, int id_)
        : time(t), type(ty), side(s),
          price(p), quantity(q), id(id_) {}
};

}

