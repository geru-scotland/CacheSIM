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
            return true;
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
            return true;
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

    /**
     * Busco la primera posición vacía
     * Si no la hay, entonces aplico el algoritmo
     * que corresponda.
     */

    if(m_algorithm == ALGORITHM_FIFO){ // Por orden de entrada

    }else if(m_algorithm == ALGORITHM_LRU){ // Por menos uso
        cElement->lruCounter = getBlockNumAndReduceLRU(cElement->setId);
        int cPos = getLruOrEmpty(cElement->setId);
        if(cPos != -1){
            cElement->blMc = cPos;
            m_cacheDir[cPos] = cElement;
        }
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

int CacheMap::getLruOrEmpty(int set) {

    int lower = CACHE_NUM_BLOCKS;
    int cachePos = -1;
    int i = 0;
    int setMax = 0; // si conju
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr){
            if(set == -1){ // Total assoc
                if(m_cacheDir[i]->lruCounter < lower){
                    lower = m_cacheDir[i]->lruCounter;
                    cachePos = i;
                }
            } else{ // Set assoc
                if(m_cacheDir[i]->setId == set){
                    setMax++;
                    if(m_cacheDir[i]->lruCounter < lower){
                        lower = m_cacheDir[i]->lruCounter;
                        cachePos = i;
                    }
                }
            }
        }
        else{
            if(m_setSize == CACHE_NUM_BLOCKS || (setMax < (CACHE_NUM_BLOCKS / m_setSize)))
                return i;
        }

        i++;
    }
    return cachePos;
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
            << " | blMP: " << int(m_cacheDir[i]->blMp) << " | LRU: " << int(m_cacheDir[i]->lruCounter) << std::endl;
        }

        i++;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}