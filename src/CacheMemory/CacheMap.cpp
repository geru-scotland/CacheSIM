//
// Created by Basajaun on 27/9/22.
//

#include <iostream>
#include "CacheMap.h"


CacheMap::CacheMap(int algorithm, int setSize){
    m_algorithm = algorithm;
    m_setSize = setSize;
}

/**
 * Se inserta en el blMc a la "fuerza", le da igual el algoritmo de reemplazo.
 * Por lo tanto, en el mapa de cache, vas a la blMC y lo cambias.
 * @param tag
 * @param blMp
 * @param blMc
 */
bool CacheMap::addrCheckByDirect(int tag, int blMp, int blMc) {
#ifdef DEBUG
    std::cout <<"[CACHE MAP][DIRECT] tag: "<< int(tag) <<"| blMP: " << int(blMp) << "| blMC: " << int(blMc) << std::endl;
#endif //DEBUG

    int i = 0;
    while(i < CACHE_NUM_BLOCKS){

        if(m_cacheDir[i] != nullptr && (m_cacheDir[i]->tag == tag) && (m_cacheDir[i]->blMp == blMp) && (i == blMc))
            return true;
        else
            i++;
    }
    // No existía, la inserto en cache y devuelvo false para que se sepa que
    // Ha habido fallo.
    CacheElement* newBlock = new CacheElement;
    newBlock->tag = tag;
    newBlock->blMp = blMp;
    newBlock->blMc = blMc;
    m_cacheDir[blMc] = newBlock;
    return false;
}

bool CacheMap::addrCheckBySetAssoc(int tag, int blMp, int setId) {
#ifdef DEBUG
    std::cout <<"[CACHE MAP][SET ASSOC] tag: "<< int(tag) <<"| blMp: " << int(blMp) << "| setId: " << int(setId) << std::endl;
#endif //DEBUG
    int i = 0;
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr && (m_cacheDir[i]->tag == tag) && (m_cacheDir[i]->setId == setId)){
            m_cacheDir[i]->lruCounter = getBlockNumAndReduceLRU(setId);
            return true; // Si HIT, ¿hay que actualizar LRU-FIFO?
        }
        else
            i++;
    }

    CacheElement* ce = new CacheElement();
    ce->tag = tag;
    ce->blMp = blMp;
    ce->setId = setId;

    manageCacheInsertion(ce);

    return false;
}

bool CacheMap::addrCheckByTotAssoc(int tag) {
#ifdef DEBUG
    std::cout <<"[CACHE MAP][TOT ASSOC] blMp: " << int(blMp) << std::endl;
#endif //DEBUG
    int i = 0;
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr && (m_cacheDir[i]->tag == tag)){
            m_cacheDir[i]->lruCounter = getBlockNumAndReduceLRU();
            return true;  // Si HIT, ¿hay que actualizar LRU-FIFO?
        }
        else
            i++;
    }

    CacheElement* ce = new CacheElement();
    ce->tag = tag;
    ce->blMp = tag;
    ce->setId = -1;

    manageCacheInsertion(ce);

    return false;
}

void CacheMap::manageCacheInsertion(CacheElement* cElement) {

    void (*pFunc)(int, int &, int &, int) = nullptr;

    if(m_algorithm == ALGORITHM_FIFO){ // Por orden de entrada
        cElement->fifoCounter = 0;
        increaseFIFOCounters(cElement->setId); // TODO: Y SI ES HIT? Hay que incrementar también
        pFunc = compareAsc;
    }else if(m_algorithm == ALGORITHM_LRU){
        cElement->lruCounter = getBlockNumAndReduceLRU(cElement->setId);
        cElement->fifoCounter = -1;
        pFunc = compareDesc;
    }

    int cPos = getCachePosOrEmpty(cElement->setId, pFunc);
    if(cPos != -1){
        cElement->blMc = cPos;
        m_cacheDir[cPos] = cElement;
    }
}

int CacheMap::getBlockNumAndReduceLRU(int set) {

    int i = 0;
    int amount = 0;
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr){
            if(set == -1){ // Total assoc
                amount++;
                m_cacheDir[i]->lruCounter--;
            } else{ // set assoc
                if(m_cacheDir[i]->setId == set){
                    amount++;
                    m_cacheDir[i]->lruCounter--;
                }
            }
        }
        i++;
    }
    return amount;
}


int CacheMap::getCachePosOrEmpty(int set, void(*compareFuncPtr)(int, int&, int&, int)) {

    /**
     * Creo que a la hora de hacer con FIFO, sería igual
     * pero en lugar de buscar el lower, sería buscar el higher.
     *
     * Mirar a ver si puedes hacer esto con template o similar mejor.
     */
    int cmp = (m_algorithm == ALGORITHM_FIFO) ? 0 : CACHE_NUM_BLOCKS;

    int cachePos = -1;
    int i = 0;
    int setMax = 0; // si conju
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr){

            int counter = m_cacheDir[i]->fifoCounter == -1 ? m_cacheDir[i]->lruCounter : m_cacheDir[i]->fifoCounter;

            if(set == -1){ // Total assoc
                compareFuncPtr(counter, (int &)cmp, (int &)cachePos, i);
            } else{ // Set assoc
                if(m_cacheDir[i]->setId == set){
                    setMax++;
                    compareFuncPtr(counter, (int &)cmp, (int &)cachePos, i);
                }
            }
        }
        else
            if(m_setSize == CACHE_NUM_BLOCKS || (setMax < (CACHE_NUM_BLOCKS / m_setSize)))
                return i;

        i++;
    }
    return cachePos;
}

void CacheMap::increaseFIFOCounters(int set){
    int i = 0;
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr){
            if(set == -1){ // Total assoc
                m_cacheDir[i]->fifoCounter++;
            } else{ // set assoc
                if(m_cacheDir[i]->setId == set){
                    m_cacheDir[i]->fifoCounter++;
                }
            }
        }
        i++;
    }
}

void CacheMap::display(){

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "CACHE CONTENT" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    int i = 0;
    while(i < CACHE_NUM_BLOCKS){

        if(m_cacheDir[i] != nullptr){
            std::cout << "CacheBlock: " << int(m_cacheDir[i]->blMc) << " Set: "<< int(m_cacheDir[i]->setId)<<"| tag: " << int(m_cacheDir[i]->tag)
            << " | blMP: " << int(m_cacheDir[i]->blMp) << " | LRU: " << int(m_cacheDir[i]->lruCounter) <<  "| FIFO: " << int(m_cacheDir[i]->fifoCounter) << std::endl;
        }

        i++;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}