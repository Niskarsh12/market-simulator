#include "market/Simulator.h"
#include <iostream>

namespace market {

Simulator::Simulator()
    : current_time(0.0) {

    log_file.open("market_log.csv");
    log_file << "time,bid,ask,last\n";
}

Simulator::~Simulator() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Simulator::schedule(const Event& e) {
    event_queue.push(e);
}

void Simulator::run() {
    while (!event_queue.empty()) {
        Event e = event_queue.pop();

        current_time = e.time;

        handle_event(e);
        log_state();
        print_state(e);
    }
}

void Simulator::handle_event(const Event& e) {
    if (e.type == EventType::OrderArrival) {

        if (e.side == Side::Buy) {
            if (state.best_ask > 0 && e.price >= state.best_ask) {
                state.last_price = state.best_ask;
                state.best_ask = 0.0;
            } else {
                state.best_bid = e.price;
            }
        } else { // Sell
            if (state.best_bid > 0 && e.price <= state.best_bid) {
                state.last_price = state.best_bid;
                state.best_bid = 0.0;
            } else {
                state.best_ask = e.price;
            }
        }
    }
}

void Simulator::log_state() {
    log_file << current_time << ","
             << state.best_bid << ","
             << state.best_ask << ","
             << state.last_price << "\n";
}

void Simulator::print_state(const Event& e) const {
    std::cout << "[t=" << current_time << "] ";

    if (e.type == EventType::OrderArrival) {
        std::cout << "OrderArrival "
                  << (e.side == Side::Buy ? "BUY " : "SELL ")
                  << "@ " << e.price << " | ";
    }

    std::cout << "Bid: " << state.best_bid
              << " Ask: " << state.best_ask
              << " Last: " << state.last_price
              << "\n";
}

} // namespace market
