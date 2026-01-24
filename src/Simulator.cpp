#include "market/Simulator.h"
#include <iostream>
#include <random>

namespace market {

// ---------- random helper ----------
double random_double(double min, double max) {
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

// ---------- core loop ----------
void Simulator::run() {
    while (!event_queue.empty()) {
        Event e = event_queue.pop();
        current_time = e.time;

        handle_event(e);
        log_state();
        print_state(e);
    }
}

// ---------- market rules ----------
void Simulator::handle_event(const Event& e) {
    if (e.type != EventType::OrderArrival)
        return;

    if (e.side == Side::Buy) {
        if (state.best_ask > 0 && e.price >= state.best_ask) {
            state.last_price = state.best_ask;
            state.best_ask = 0.0;
        } else {
            if (state.best_bid == 0.0 || e.price > state.best_bid) {
                state.best_bid = e.price;
            }
        }
    } else { // Sell
        if (state.best_bid > 0 && e.price <= state.best_bid) {
            state.last_price = state.best_bid;
            state.best_bid = 0.0;
        } else {
            if (state.best_ask == 0.0 || e.price < state.best_ask) {
                state.best_ask = e.price;
            }
        }
    }
}
    
// ---------- logging ----------
void Simulator::log_state() {
    log_file << current_time << ","
             << state.best_bid << ","
             << state.best_ask << ","
             << state.last_price << "\n";
}

// ---------- debug ----------
void Simulator::print_state(const Event& e) const {
    std::cout << "[t=" << current_time << "] ";

    std::cout << (e.side == Side::Buy ? "BUY " : "SELL ")
              << "@ " << e.price
              << " | Bid: " << state.best_bid
              << " Ask: " << state.best_ask
              << " Last: " << state.last_price
              << "\n";
}

} // namespace market
