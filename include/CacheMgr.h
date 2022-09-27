//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_CACHEMGR_H
#define CACHESIM_CACHEMGR_H


#include <cstdint>

/**
 * Clase encargada de gestionar la memoria completamente.
 */
class CacheMgr {

public:
    CacheMgr();
    void setConfig(int16_t wordSize, int16_t blockSize, int8_t setSize, int8_t replaceAlgorithm);

    int16_t getWordSize();
    int16_t getBlockSize();
    int8_t getSetSize();
    int8_t getReplacementAlgorithm();

    void manageNewOperation(int16_t addr, bool opcode);

private:
    int16_t m_wordSize;
    int16_t m_blockSize;
    int8_t m_setSize;
    int8_t m_replaceAlgorithm;

    bool createCacheMap();
};

#endif //CACHESIM_CACHEMGR_H