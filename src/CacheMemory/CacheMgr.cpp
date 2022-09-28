//
// Created by Basajaun on 27/9/22.
//

#include <iostream>
#include <cmath>
#include "CacheMgr.h"

CacheMgr::CacheMgr() {

}

void CacheMgr::setConfig(int wordSize, int blockSize, int setSize, int algorithm) {
    m_wordSize = wordSize;
    m_blockSize = blockSize;
    m_setSize = setSize;
    m_replaceAlgorithm = algorithm;
    cacheMap = new CacheMap(algorithm, setSize);
}

void CacheMgr::manageNewOperation(int addr, bool opcode) {

    int blockBits = int(log2(CACHE_NUM_BLOCKS));
    int wordBits = int(log2(m_blockSize / m_wordSize));
    int byteBits = int(log2(m_wordSize));
    int tag = 0;
    int blMp = int(addr / pow(2, wordBits + byteBits));

    cacheMap->setOpcode(opcode);

    switch(m_setSize) {
        case ASSOC_DIRECT:
        {
            int blMc = int(blMp % int(pow(2, blockBits)));
            tag = int(blMp / pow(2, blockBits));

            if(cacheMap->addrCheckByDirect(tag, blMp, blMc))
            {
                //Acierto. Mostrar calculos
                std::cout << std::endl;
                std::cout << "HIT!" << std::endl;
            }else{
                //Miss, lo traes. Mostrar calculos
                std::cout << std::endl;
                std::cout << "MISS!" << std::endl;
            }
            break;
        }
        case ASSOC_SET_2:
        case ASSOC_SET_4:
        {
            int setBits = int(log2(m_setSize));
            int setId = blMp % int(pow(2, setBits));
            tag = int(blMp / pow(2, setBits));
            if(cacheMap->addrCheckBySetAssoc(tag, blMp, setId))
            {
                //Acierto
            }
            else{

            }
            break;
        }
        case ASSOC_TOTAL:
            if(cacheMap->addrCheckByTotAssoc(blMp))
            {
                std::cout << std::endl;
                std::cout << "HIT!" << std::endl;
            }
            else{

            }
            break;
        default:
            break;
    }

    cacheMap->display();
}