#include "market/Simulator.h"
#include <iostream>

namespace market {

Simulator::Simulator()
    : current_time(0.0) {}

// Schedule a future event
void Simulator::schedule(const Event& e) {
    event_queue.push(e);
}

// Core simulation loop
void Simulator::run() {
    while (!event_queue.empty()) {
        Event e = event_queue.pop();

        // advance simulation time
        current_time = e.time;

        // apply event to market state
        handle_event(e);

        // debug output (temporary)
        print_state(e);
    }
}

// Apply market rules
void Simulator::handle_event(const Event& e) {
    if (e.type == EventType::OrderArrival) {

        if (e.side == Side::Buy) {

            // If buy price crosses ask → trade
            if (state.best_ask > 0 && e.price >= state.best_ask) {
                state.last_price = state.best_ask;
                state.best_ask = 0.0;  // consumed
            } 
            // Otherwise update bid
            else {
                state.best_bid = e.price;
            }

        } else { // Sell order

            // If sell price crosses bid → trade
            if (state.best_bid > 0 && e.price <= state.best_bid) {
                state.last_price = state.best_bid;
                state.best_bid = 0.0;  // consumed
            }
            // Otherwise update ask
            else {
                state.best_ask = e.price;
            }
        }
    }
}

// Print current state (for debugging)
void Simulator::print_state(const Event& e) const {
    std::cout << "[t=" << current_time << "] ";

    if (e.type == EventType::OrderArrival) {
        std::cout << "OrderArrival ";
        std::cout << (e.side == Side::Buy ? "BUY " : "SELL ");
        std::cout << "@ " << e.price << " | ";
    }

    std::cout << "Bid: " << state.best_bid
              << " Ask: " << state.best_ask
              << " Last: " << state.last_price
              << "\n";
}

} // namespace market
