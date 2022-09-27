//
// Created by Basajaun on 27/9/22.
//

#include "CacheMgr.h"
#include "math.h"

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
    /*
     * Extraer tag, conjunto, palabra y tal, en base al numero de conjuntos.
     * Buscar en el mapa de cache
     * Ver si lectura, escritura.
     * Hit/Miss
     *
     * El tema ¿como busco en el mapa cache? Aqui es donde influye el tipo de correspondencia.
     * 1) Directa (blMp busca en el directorio y devuelve bloque asociado)
     * 2) Totalmente Asociativa (tag
     * 3) Por conjuntos (busca en conjunto && tag)
     */
    // Bits required to direct a block, the word and the byte.
    int blockBits = (int)log2(CACHE_NUM_BLOCKS);
    int wordBits = (int)log2(m_blockSize / m_wordSize);
    int byteBits = (int)log2(m_wordSize);

}

bool CacheMgr::createCacheMap() {
    /**
     * Lo creo, pero va a estar vacio, se va "rellenenando" la cache
     * segun se van efectuando operaciones.
     */

}