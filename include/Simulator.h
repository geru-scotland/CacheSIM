//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_SIMULATOR_H
#define CACHESIM_SIMULATOR_H

#include "CacheMgr.h"

/**
 * Cache: 8 blocks
 * Block size: 32 or 64 bytes.
 * Word size: 4 or 8 bytes.
 *
 * E.g: 32 block size and 4 word size = 8 words.
 * 8 blocks, 32 bytes each = 256 bytes.
 * Total cache memory size: 256 bytes. (2^n = 256 -> 8 bits)
 *
 * 32 (block size) / 4 (word size) = 8 words. 3 bits.
 * 8 blocks -> 3 bits (in order to redirect any block).
 * 2 bits.
 *
 * Matrix 8x5 (8 line/block 5 parameters)
 */

class Simulator {
public:
    Simulator();
    void initConfig();
    int16_t newAddress();

private:
    CacheMgr* cm;
};


#endif //CACHESIM_SIMULATOR_H
