//
// Created by Basajaun on 27/9/22.
//

#include <iostream>
#include "CacheMap.h"


CacheMap::CacheMap(){

}

/**
 * Se inserta en el blMc a la "fuerza", le da igual el algoritmo de reemplazo.
 * Por lo tanto, en el mapa de cache, vas a la blMC y lo cambias.
 * @param tag
 * @param blMp
 * @param blMc
 */
void CacheMap::addrCheckByDirect(int tag, int blMp, int blMc) {
#ifdef DEBUG
    std::cout <<"[CACHE MAP][DIRECT] tag: "<< int(tag) <<"| blMP: " << int(blMp) << "| blMC: " << int(blMc) << std::endl;
#endif //DEBUG
}

void CacheMap::addrCheckBySetAssoc(int tag, int blMp, int setId) {
#ifdef DEBUG
    std::cout <<"[CACHE MAP][SET ASSOC] tag: "<< int(tag) <<"| blMp: " << int(blMp) << "| setId: " << int(setId) << std::endl;
#endif //DEBUG
}

void CacheMap::addrCheckByTotAssoc(int blMp) {
#ifdef DEBUG
    std::cout <<"[CACHE MAP][TOT ASSOC] blMp: " << int(blMp) << std::endl;
#endif //DEBUG
}