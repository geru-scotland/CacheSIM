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


    //Todo: Implementar con flags bitwise mejor.
    bool dirty = false;
    bool replaced = false;
};

/**
 * Clase encargada de gestionar la estructura de nuestra memoria cache
 * en función de cada instrucción dada.
 * Estructura base para representar la memoria cache:
 * Array de punteros a struct del tipo CacheElement.
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
    void displayDirect();
    void displayTotalAsoc();
    void displaySetAssoc();

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