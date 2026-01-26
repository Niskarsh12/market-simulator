#include "market/Simulator.h"

#include <iostream>
#include <random>
#include <algorithm>

namespace market {


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

// ------- agent registration ---------

void Simulator::add_agent(std::unique_ptr<Agent>agent){
    agents.push_back(std::move(agent));
}

// ---------- core simulation loop ----------

void Simulator::run(double end_time){
    while (current_time < end_time) {

        //ask each agent to act
        for (auto& agent : agents) {
            Event e =
agent->act(current_time, state);
           event_queue.push(e);            
        }

        if (event_queue.empty())
            break;

        // execute next event in time
        Event ev = event_queue.pop();
        current_time = ev.time;
        
        handle_event(ev);
        log_state();
        print_state(ev);
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
