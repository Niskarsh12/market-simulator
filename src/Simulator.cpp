#include "market/Simulator.h"

#include <iostream>
#include <random>
#include <algorithm>

namespace market {

// ---------- random helper ----------
static double random_double(double min, double max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}

// ---------- lifecycle ----------
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

// ---------- scheduling ----------
void Simulator::schedule(const Event& e) {
    event_queue.push(e);
}

// ---------- random order flow ----------
void Simulator::generate_random_orders(int count) {
    double t = current_time;

    for (int i = 0; i < count; i++) {
        t += random_double(0.1, 1.0);

        Side side = (random_double(0.0, 1.0) < 0.5)
                        ? Side::Buy
                        : Side::Sell;

        double base_price = (state.last_price > 0.0)
                                ? state.last_price
                                : 100.0;

        double price = base_price + random_double(-5.0, 5.0);

        schedule(Event(
            t,
            EventType::OrderArrival,
            side,
            price,
            1,
            i
        ));
    }
}

// ---------- core simulation loop ----------
void Simulator::run() {
    while (!event_queue.empty()) {
        Event e = event_queue.pop();
        current_time = e.time;

        handle_event(e);
        log_state();
        print_state(e);
    }
}

// ---------- order book logic ----------
void Simulator::handle_event(const Event& e) {
    if (e.type != EventType::OrderArrival)
        return;

    // BUY order
    if (e.side == Side::Buy) {
        if (!state.asks.empty() && e.price >= state.asks.front()) {
            // trade at best ask
            state.last_price = state.asks.front();
            state.asks.erase(state.asks.begin());
        } else {
            state.bids.push_back(e.price);
            std::sort(state.bids.begin(), state.bids.end(), std::greater<>());
        }
    }
    // SELL order
    else {
        if (!state.bids.empty() && e.price <= state.bids.front()) {
            // trade at best bid
            state.last_price = state.bids.front();
            state.bids.erase(state.bids.begin());
        } else {
            state.asks.push_back(e.price);
            std::sort(state.asks.begin(), state.asks.end());
        }
    }
}

// ---------- CSV logging ----------
void Simulator::log_state() {
    double best_bid = state.bids.empty() ? 0.0 : state.bids.front();
    double best_ask = state.asks.empty() ? 0.0 : state.asks.front();

    log_file << current_time << ","
             << best_bid << ","
             << best_ask << ","
             << state.last_price << "\n";
}

// ---------- console output ----------
void Simulator::print_state(const Event& e) const {
    double best_bid = state.bids.empty() ? 0.0 : state.bids.front();
    double best_ask = state.asks.empty() ? 0.0 : state.asks.front();

    std::cout << "[t=" << current_time << "] "
              << (e.side == Side::Buy ? "BUY " : "SELL ")
              << "@ " << e.price
              << " | Bid: " << best_bid
              << " Ask: " << best_ask
              << " Last: " << state.last_price
              << "\n";
}

} // namespace market
