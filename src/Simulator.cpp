#include "market/Simulator.h"
#include "market/MarketState.h"
#include <iostream>
#include <algorithm>

namespace market {

// ---------- lifecycle ----------

Simulator::Simulator(SimulationConfig cfg)
    : current_time(0.0),
      processed_events(0),
      config(cfg),
      rng(cfg.seed) {

    log_file.open("market_log.csv");
    log_file << "time,bid,ask,last\n";
}

Simulator::~Simulator() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

// ---------- agent registration ----------

void Simulator::add_agent(std::unique_ptr<Agent> agent) {
    agents.push_back(std::move(agent));
}

// ---------- core simulation loop ----------

void Simulator::run(double end_time) {
    std::uniform_real_distribution<double> dt_dist(
        config.min_dt, config.max_dt
    );

    while (current_time < end_time &&
           processed_events < config.max_events) {

        // generate events from agents
        for (auto& agent : agents) {
            double dt = dt_dist(rng);
            current_time += dt;

            Event e = agent->act(current_time, state);
            event_queue.push(e);
        }

        // process all queued events
        while (!event_queue.empty()) {
            Event e = event_queue.pop();
            handle_event(e);
            print_state(e);
            log_state();
            processed_events++;
        }
    }
}

// ---------- event handling ----------

void Simulator::handle_event(const Event& e) {
    if (e.side == Side::Buy) {
        if (state.best_ask > 0 && e.price >= state.best_ask) {
            // trade happens
            state.last_price = state.best_ask;
            state.best_ask = 0.0;
        } else {
            if (state.best_bid == 0.0 || e.price > state.best_bid) {
                state.best_bid = e.price;
            }
        }
    } else { // Sell
        if (state.best_bid > 0 && e.price <= state.best_bid) {
            // trade happens
            state.last_price = state.best_bid;
            state.best_bid = 0.0;
        } else {
            if (state.best_ask == 0.0 || e.price < state.best_ask) {
                state.best_ask = e.price;
            }
        }
    }
}

// ---------- logging & debug ----------

void Simulator::log_state() {
    log_file
        << current_time << ","
        << state.best_bid << ","
        << state.best_ask << ","
        << state.last_price << "\n";
}

void Simulator::print_state(const Event& e) const {
    std::cout << "[t=" << current_time << "] "
              << (e.side == Side::Buy ? "BUY " : "SELL ")
              << "@ " << e.price
              << " | Bid: " << state.best_bid
              << " Ask: " << state.best_ask
              << " Last: " << state.last_price
              << "\n";
}

} // namespace market
