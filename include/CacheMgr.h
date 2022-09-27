//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_CACHEMGR_H
#define CACHESIM_CACHEMGR_H

#include <cstdint>
#include "CacheMap.h"


/**
 * Clase encargada de gestionar la memoria completamente.
 */
class CacheMgr {

public:
    CacheMgr();
    void setConfig(int wordSize, int blockSize, int setSize, int replaceAlgorithm);

    int getWordSize();
    int getBlockSize();
    int getSetSize();
    int getReplacementAlgorithm();

    void manageNewOperation(int addr, bool opcode);


private:
    int m_wordSize;
    int m_blockSize;
    int m_setSize;
    int m_replaceAlgorithm;
    CacheMap* cacheMap;

};

#endif //CACHESIM_CACHEMGR_H