//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_CACHEMAP_H
#define CACHESIM_CACHEMAP_H

#include "SharedDefines.h"

typedef struct {
    int blMp;
    int blMc;
    int tag;
    int lruCounter;
    bool free;
    int fifoOrder;
} Block;

/**
 * Matriz de punteros a blocks
 */
class CacheMap {

public:
    CacheMap(int algorithm);

    bool addrCheckByDirect(int tag, int blMp, int blMc);
    bool addrCheckBySetAssoc(int tag, int blMp, int setId);
    bool addrCheckByTotAssoc(int blMp);

    /**
     * LRU
     */
    int getCurrentBlockAmountAndReduceLRU();
    int getLeastRecentlyUsedBlockOrEmpty();

    void display();

private:
    Block* m_cacheDir[CACHE_NUM_BLOCKS]{};
    int m_algorithm;
};

#endif //CACHESIM_CACHEMAP_H