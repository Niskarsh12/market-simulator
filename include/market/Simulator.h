#pragma once


#include "EventQueue.h"
#include "Event.h"
#include "MarketState.h"
#include "Agent.h"
#include <memory>
#include <vector>

#include <fstream>

namespace market {

class Simulator {
public:
    Simulator();
    ~Simulator();

    void add_agent(std::unique_ptr<Agent>agent);
    void run(double end_time);


private:
    double current_time;
    EventQueue event_queue;
    MarketState state;

    std::vector<std::unique_ptr<Agent>>agents;
    std::ofstream log_file;

    void handle_event(const Event& e);
    void print_state(const Event& e) const;
    void log_state();
};

} // namespace market



