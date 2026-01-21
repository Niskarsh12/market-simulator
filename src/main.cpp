#include "market/Simulator.h"

int main() {
    market::Simulator sim;

    // create random market activity
    sim.generate_random_orders(100);

    // run simulation
    sim.run();

    return 0;
}
