#include <iostream>
#include <Simulator.h>

using namespace  std;

int main() {

    Simulator sim; // Stack
    sim.initConfig();

    int16_t addr = 0;

    while(addr != -1){
        addr = sim.newAddress();
    }
    // Show Global access data / Time.
    // Clase stática que lo controle.
    return 0;
}
