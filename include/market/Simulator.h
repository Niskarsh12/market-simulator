#pragma once

#include "EventQueue.h"
#include "Event.h"
#include "MarketState.h"
#include "Agent.h"
#include "SimulationConfig.h"

#include <memory>
#include <vector>
#include <fstream>
#include <random>
#include <cstdint>

namespace market {

class Simulator {
public:
    explicit Simulator(SimulationConfig cfg);
    ~Simulator();

    void add_agent(std::unique_ptr<Agent> agent);
    void run(double end_time);

private:
    // ---- simulation state ----
    double current_time;
    std::uint64_t processed_events;

    EventQueue event_queue;
    MarketState state;
    SimulationConfig config;

    // ---- agents ----
    std::vector<std::unique_ptr<Agent>> agents;

    // ---- randomness & logging ----
    std::mt19937 rng;
    std::ofstream log_file;

    // ---- internals ----
    void handle_event(const Event& e);
    void print_state(const Event& e) const;
    void log_state();
};

} // namespace market

