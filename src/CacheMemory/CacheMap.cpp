//
// Created by Basajaun on 27/9/22.
//

#include <iostream>
#include "CacheMap.h"


CacheMap::CacheMap(int setSize){

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
    std::cout << "[CACHE-REEMPLAZO][WRITE-BACK] Enviando al búfer el bloque antes de sobreescribirlo.";
    Block* newBlock = new Block;
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
    /**
     * Acierte o no, creo que hay que actualizar los LRU
     */
    return false;
}

bool CacheMap::addrCheckByTotAssoc(int blMp) {
#ifdef DEBUG
    std::cout <<"[CACHE MAP][TOT ASSOC] blMp: " << int(blMp) << std::endl;
#endif //DEBUG
    return false;
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
            std::cout << "Bloque: " << int(m_cacheDir[i]->blMc) << " | tag: " << int(m_cacheDir[i]->tag)
            << " | blMP: " << int(m_cacheDir[i]->blMp) << std::endl;
        }

        i++;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}