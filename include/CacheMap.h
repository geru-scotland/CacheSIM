//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_CACHEMAP_H
#define CACHESIM_CACHEMAP_H

#include "SharedDefines.h"

struct CacheElement{
    int blMp = -1;
    int blMc = -1;
    int tag = -1;
    int setId = -1;

    int lruCounter = 0;
    int fifoCounter = 0;

    /**
     * Implementar con flags bitwise mejor.
     */
    bool free = false; //TODO: Hardcodear en display, if nullptr, que ponga free y quitar esto.
    bool dirty = false;
    bool replaced = false;
};

/**
 * Matriz de punteros a CacheElement
 */
class CacheMap {

public:
    CacheMap(int algorithm, int setSize);
    void setOpcode(int opcode);

    bool addrCheckByDirect(int tag, int blMp, int blMc);
    bool addrCheckBySetAssoc(int tag, int blMp, int setId);
    bool addrCheckByTotAssoc(int blMp);

    /**
     * Display
     */
    void setDisplayMode(DisplayMode mode);
    void display();

private:
    void manageCacheInsertion(CacheElement* ce);

    /**
     * LRU
     */
    int getBlockNumAndReduceLRU(int set = -1);
    int getCachePosOrEmpty(int set = -1, void (*compareFuncPtr)(int, int&, int&, int) = nullptr);

    /**
     * FIFO
     */
    void increaseFIFOCounters(int set = -1);

    CacheElement* m_cacheDir[CACHE_NUM_BLOCKS]{};
    DisplayMode m_displayMode;
    int m_algorithm;
    int m_setSize;
    int m_opcode;
};

#endif //CACHESIM_CACHEMAP_H