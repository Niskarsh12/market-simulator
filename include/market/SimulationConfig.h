#pragma once
#include <cstdint>

namespace market {
    struct SimulationConfig {
        double min_dt = 0.1;
        double max_dt = 1.0;

        std::uint64_t max_events = 10000;
        unsigned int seed = 42;
    };
}