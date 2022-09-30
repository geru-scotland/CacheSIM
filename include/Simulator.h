//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_SIMULATOR_H
#define CACHESIM_SIMULATOR_H

#include "CacheMgr.h"

class Simulator {
public:
    Simulator();
    void initConfig();
    int16_t newAddress();

private:
    CacheMgr* cMgr;
};


#endif //CACHESIM_SIMULATOR_H
