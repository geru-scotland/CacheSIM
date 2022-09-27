//
// Created by Basajaun on 27/9/22.
//

#include <iostream>
#include "CacheMgr.h"
#include "math.h"

CacheMgr::CacheMgr() {

}

void CacheMgr::setConfig(int wordSize, int blockSize, int setSize, int replaceAlgorithm) {
    m_wordSize = wordSize;
    m_blockSize = blockSize;
    m_setSize = setSize;
    m_replaceAlgorithm = replaceAlgorithm;
    cacheMap = new CacheMap(setSize);
}

int CacheMgr::getWordSize(){
    return m_wordSize;
}

int CacheMgr::getBlockSize(){
    return m_blockSize;
}

int CacheMgr::getSetSize(){
    return m_setSize;
}

int CacheMgr::getReplacementAlgorithm(){
    return m_replaceAlgorithm;
}

void CacheMgr::manageNewOperation(int addr, bool opcode) {
    /*
     * Extraer tag, conjunto, palabra y tal, en base al numero de conjuntos.
     * Buscar en el mapa de cache
     * Ver si lectura, escritura.
     * Hit/Miss
     *
     * El tema ¿como busco en el mapa cache? Aqui es donde influye el tipo de correspondencia.
     * 1) Directa (tag + bloque)
     * 2) Totalmente Asociativa (tag únicamente)
     * 3) Por conjuntos (busca en conjunto && tag)
     */
    // Bits required to direct a block, the word and the byte.
    int blockBits = int(log2(CACHE_NUM_BLOCKS));
    int wordBits = int(log2(m_blockSize / m_wordSize));
    int byteBits = int(log2(m_wordSize));
    int tag = 0;
    int blMp = int(addr / pow(2, wordBits + byteBits));  // Bloque a guardar en MC, es la referencia base.

    switch(m_setSize) {
        case 1: // Directa(blMP = tag + bloqueMc)
        {
            int blMc = int(blMp % int(pow(2, blockBits)));
            tag = int(blMp / pow(2, blockBits));
            // Si no existe por tag -> FALLO. Y lo "Traigo" / inserto en el mapa.
            // Siguiendo el tipo de Algoritmo, cuidado con los LRU, contadores y tal
            if(cacheMap->addrCheckByDirect(tag, blMp, blMc))
            {
                //Acierto. Mostrar calculos
            }else{
                //Miss, lo traes. Mostrar calculos
            }
            break;
        }
        case 2: // Asociativa por conjuntos (blMP = tag + conjunto)
        case 4:
        {
            int setBits = int(log2(m_setSize));
            int setId = blMp % int(pow(2, setBits));
            tag = int(blMp / pow(2, setBits));
            if(cacheMap->addrCheckBySetAssoc(tag, blMp, setId))
            {
                //Acierto
            }
            else{
                // Miss, traerlo en base al algoritmo actual
                // SI LRU, el que más puntos LRU tenga en ESE conjunto, es el que se sustituye
                // Dar tag. blMp y setID (quiza también)
            }
            break;
        }
        case 8: // Totalmente asociativa (blMp)
            if(cacheMap->addrCheckByTotAssoc(blMp))
            {
                // acierto
            }
            else{
                //Miss, lo metes done "se pueda", en base al algoritmo.
                // Recuerda que los algoritmos únicamente surten efecto
                // Cuando los 8 bloques de la cache estén llenos.
                // En asocitavia tot, se meten en el primer bloque con hueco
                // En por conjuntos, en el primer hueco del conjunto.
            }
            break;
        default:
            break;
    }

    cacheMap->display();
}

bool CacheMgr::createCacheMap() {
    /**
     * Lo creo, pero va a estar vacio, se va "rellenenando" la cache
     * segun se van efectuando operaciones.
     */
}