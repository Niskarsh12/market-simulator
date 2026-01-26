#include "market/Simulator.h"
#include "market/NoiseAgent.h"

int main() {
    market::Simulator sim;

    // Add multiple noise agents

sim.add_agent(std::make_unique<market::NoiseAgent>(1)); 
sim.add_agent(std::make_unique<market::NoiseAgent>(2));    
sim.add_agent(std::make_unique<market::NoiseAgent>(3));       


    sim.run(50.0);
    return 0;
}
