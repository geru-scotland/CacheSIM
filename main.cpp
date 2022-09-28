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

    cout << "[DATA] Total cicles: "<< DataMgr::getTotalCicles() << endl;
    cout << "[DATA] Total accesses: "<< DataMgr::getTotalAccesses() << endl;
    cout << "[DATA] Total hits: "<< DataMgr::getTotalHits() << endl;
    cout << "--------------------------"<< endl;
    cout << "[DATA] Hit Rate:  "<< DataMgr::getHitRate() << endl;
    return 0;
}
