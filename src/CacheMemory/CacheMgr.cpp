//
// Created by Basajaun on 27/9/22.
//

#include "CacheMgr.h"

CacheMgr::CacheMgr() {

}

void CacheMgr::setConfig(int16_t wordSize, int16_t blockSize, int8_t setSize, int8_t replaceAlgorithm) {
    m_wordSize = wordSize;
    m_blockSize = blockSize;
    m_setSize = setSize;
    m_replaceAlgorithm = replaceAlgorithm;
}

int16_t CacheMgr::getWordSize(){
    return m_wordSize;
}

int16_t CacheMgr::getBlockSize(){
    return m_blockSize;
}

int8_t CacheMgr::getSetSize(){
    return m_setSize;
}

int8_t CacheMgr::getReplacementAlgorithm(){
    return m_replaceAlgorithm;
}

void CacheMgr::manageNewOperation(int16_t addr, bool opcode) {

}

bool CacheMgr::createCacheMap() {

}