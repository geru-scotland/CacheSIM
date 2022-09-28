#include <iostream>
#include <Simulator.h>
#include "DataMgr.h"

using namespace  std;

int main() {

    Simulator sim; // Stack
    sim.initConfig();

    int16_t addr = 0;

    while(addr != -1){
        addr = sim.newAddress();
    }

    cout << "Total cicles: "<< DataMgr::getTotalCicles() << endl;
    return 0;
}
