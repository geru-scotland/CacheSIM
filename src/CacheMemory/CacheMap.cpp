//
// Created by Basajaun on 27/9/22.
//

#include <iostream>
#include <iomanip>
#include "CacheMap.h"
#include "DataMgr.h"

using namespace std;

CacheMap::CacheMap(int algorithm, int setSize){
    m_algorithm = algorithm;
    m_setSize = setSize;
}

void CacheMap::setOpcode(int opcode){
    m_opcode = opcode;
}

/**
 * Método que gestiona lo relativo a la correspondencia directa.
 */
bool CacheMap::addrCheckByDirect(int tag, int blMp, int blMc) {
#ifdef DEBUG
    cout <<"[CACHE MAP][DIRECT] tag: "<< int(tag) <<"| blMP: " << int(blMp) << "| blMC: " << int(blMc) << endl;
#endif //DEBUG

    int i = 0;
    while(i < CACHE_NUM_BLOCKS){

        if(m_cacheDir[i] != nullptr && (m_cacheDir[i]->tag == tag) && (m_cacheDir[i]->blMp == blMp) && (i == blMc))
        {
            DataMgr::storeResultData(blMc, m_cacheDir[i]->blMp, blMp, (int)m_cacheDir[i]->dirty, m_opcode);
            if(m_opcode == OPCODE_WRITE)
                m_cacheDir[i]->dirty = true;
            return true;
        }
        else
            i++;
    }

    // Miss

    CacheElement* newBlock = new CacheElement;
    newBlock->tag = tag;
    newBlock->blMp = blMp;
    newBlock->blMc = blMc;

    if(m_cacheDir[blMc] != nullptr){
        newBlock->replaced = true;
        DataMgr::setLastOpStatus(CACHE_FLAG_REPLACED);
        DataMgr::storeResultData(blMc, m_cacheDir[blMc]->blMp, newBlock->blMp, (int)m_cacheDir[blMc]->dirty, m_opcode);
    }else
        DataMgr::storeResultData(blMc, blMc, newBlock->blMp, 0, m_opcode);

    if(m_opcode == OPCODE_WRITE)
        newBlock->dirty = true;

    m_cacheDir[blMc] = newBlock;
    return false;
}

/**
 * Método que gestiona lo relativo a la correspondencia
 * asociativa por conjuntos.
 */
bool CacheMap::addrCheckBySetAssoc(int tag, int blMp, int setId) {
#ifdef DEBUG
    cout <<"[CACHE MAP][SET ASSOC] tag: "<< int(tag) <<"| blMp: " << int(blMp) << "| setId: " << int(setId) << endl;
#endif //DEBUG
    int i = 0;
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr && (m_cacheDir[i]->tag == tag) && (m_cacheDir[i]->setId == setId)){

            DataMgr::storeResultData(i, m_cacheDir[i]->blMp, blMp, (int)m_cacheDir[i]->dirty, m_opcode);
            if(m_opcode == OPCODE_WRITE)
                m_cacheDir[i]->dirty = true;

            if(m_algorithm == ALGORITHM_LRU)
                m_cacheDir[i]->lruCounter = getBlockNumAndReduceLRU(setId);
            else
                increaseFIFOCounters(setId);

            return true;
        }
        else
            i++;
    }

    // Miss

    CacheElement* ce = new CacheElement();
    ce->tag = tag;
    ce->blMp = blMp;
    ce->setId = setId;

    manageCacheInsertion(ce);

    return false;
}

/**
 * Método que gestiona lo relativo a la correspondencia totalmente
 * asociativa.
 */
bool CacheMap::addrCheckByTotAssoc(int tag) {
#ifdef DEBUG
    cout <<"[CACHE MAP][TOT ASSOC] blMp: " << int(blMp) << endl;
#endif //DEBUG
    int i = 0;
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr && (m_cacheDir[i]->tag == tag)){
            DataMgr::storeResultData(i, m_cacheDir[i]->blMp, m_cacheDir[i]->blMp, (int)m_cacheDir[i]->dirty, m_opcode);

            if(m_opcode == OPCODE_WRITE)
                m_cacheDir[i]->dirty = true;

            if(m_algorithm == ALGORITHM_LRU)
                m_cacheDir[i]->lruCounter = getBlockNumAndReduceLRU();
            else
                increaseFIFOCounters();

            return true;
        }
        else
            i++;
    }

    // Miss

    CacheElement* ce = new CacheElement();
    ce->tag = tag;
    ce->blMp = tag;
    ce->setId = -1;

    manageCacheInsertion(ce);

    return false;
}

/**
 * Gestión de los miss para las correspondencias asociativas (ambas)
 * @param cElement Puntero a struct del tipo CacheElement
 */
void CacheMap::manageCacheInsertion(CacheElement* cElement) {

    // Puntero a función, para poder pasarla como parámetro.
    void (*pFunc)(int, int &, int &, int) = nullptr;

    if(m_opcode == OPCODE_WRITE)
        cElement->dirty = true;

    if(m_algorithm == ALGORITHM_FIFO){
        cElement->fifoCounter = 0;
        increaseFIFOCounters(cElement->setId);
        pFunc = compareAsc;
    }else if(m_algorithm == ALGORITHM_LRU){
        cElement->lruCounter = getBlockNumAndReduceLRU(cElement->setId);
        cElement->fifoCounter = -1;
        pFunc = compareDesc;
    }

    /**
     * Una vez decidida la función que se utilizará en base al
     * algoritmo seleccionado, se pasa su referencia como parámetro.
     */
    int cPos = getCachePosOrEmpty(cElement->setId, pFunc);
    if(cPos != -1){
        cElement->blMc = cPos;

        if(m_cacheDir[cPos] != nullptr)
        {
            cElement->replaced = true;
            DataMgr::setLastOpStatus(CACHE_FLAG_REPLACED);
            // Bloque Cache que se toca, BloqueMP antiguo
            DataMgr::storeResultData(cPos, m_cacheDir[cPos]->blMp, cElement->blMp, (int)m_cacheDir[cPos]->dirty);
        } else
            DataMgr::storeResultData(cPos, cElement->blMp, cElement->blMp, 0);

        m_cacheDir[cPos] = cElement;
    }
}

/**
 * Método auxiliar para el algoritmo LRU
 */
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

/**
 * Método para determinar la posición de caché que le corresponde a un
 * bloque.
 */
int CacheMap::getCachePosOrEmpty(int set, void(*compareFuncPtr)(int, int&, int&, int)) {

    int cmp = (m_algorithm == ALGORITHM_FIFO) ? 0 : CACHE_NUM_BLOCKS;
    int cachePos = -1;
    int i = 0;
    int setMax = 0;

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

/**
 * Método auxiliar para el algoritmo FIFO
 */
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

/**
 * Diferentes métodos para el output
 */
void CacheMap::setDisplayMode(DisplayMode mode) { m_displayMode = mode; }

void CacheMap::display(){

    cout << endl;
    cout << "-------------" << endl;
    cout << "CACHE CONTENT" << endl;
    cout << "-------------" << endl;
    cout << endl;

    switch(m_displayMode){
        case DISPLAY_DIRECT:
            displayDirect();
            break;
        case DISPLAY_TOTAL_ASOC:
            displayTotalAsoc();
            break;
        case DISPLAY_SET_ASOC:
            displaySetAssoc();
            break;
        default:
            break;
    }

    cout << endl;
    cout << endl;
}

void CacheMap::displayDirect() {

    cout << setw(11) << "MC (block)" << setw(4) << "|" << setw(7) << "TAG"
    << setw(7) << "|" << setw(18) << "MP (block) "<< setw(5) <<"|" << setw(9)
    << "Dirty"<< setw(7) <<"| " << setw(5) << "Repl"<< endl;
    cout << " ________________________________________________________________________"<< endl;
    cout << endl;
    int i = 0;
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr){
            cout << setw(8) << int(m_cacheDir[i]->blMc) << setw(7)
            << "|" << setw(6) << int(m_cacheDir[i]->tag) << setw(8)
            << "|" << setw(12)<< int(m_cacheDir[i]->blMp) << setw(11)
            << "|" << setw(7)<< int(m_cacheDir[i]->dirty) << setw(8)
            << "|" << setw(4)<< int(m_cacheDir[i]->replaced)<< endl;
        }

        i++;
    }
}

void CacheMap::displayTotalAsoc() {

    std::string algorithm;
    m_algorithm == ALGORITHM_LRU ? algorithm = "LRU" : algorithm = "FIFO";

    cout << setw(11) << "MC (block)" << setw(4) << "|" << setw(17) << "TAG/MP (block)"
         << setw(4) << "|" << setw(7) << algorithm << setw(5) <<"|" << setw(9)
         << "Dirty"<< setw(7) <<"| " << setw(5) << "Repl"<< endl;
    cout << " ______________________________________________________________________"<< endl;
    cout << endl;
    int i = 0;
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr){
            int counterData = m_algorithm == ALGORITHM_LRU ? int(m_cacheDir[i]->lruCounter) : int(m_cacheDir[i]->fifoCounter);
            cout << setw(8) << int(m_cacheDir[i]->blMc) << setw(9)
            << setw(18) << int(m_cacheDir[i]->blMp)  << setw(14)
            << setw(16) << int(counterData) << setw(10)
            << setw(13) << int(m_cacheDir[i]->dirty) << setw(10)
            << setw(12) << int(m_cacheDir[i]->replaced)<< endl;
        }

        i++;
    }
}

void CacheMap::displaySetAssoc() {
    std::string algorithm;
    m_algorithm == ALGORITHM_LRU ? algorithm = "LRU" : algorithm = "FIFO";

    cout << setw(11) << "MC (block)" << setw(4) << "|" << setw(5) << "SET" << setw(3) << "|" << setw(5) << "TAG"
         << setw(3) << "|" << setw(15) << "MP (block) " << setw(3) << "|" << setw(5) << algorithm << setw(3) <<"|"
         << setw(6)<< "Dirty"<< setw(4) <<"| " << setw(5) << "Repl"<< endl;
    cout << " _______________________________________________________________________"<< endl;
    cout << endl;
    int i = 0;
    while(i < CACHE_NUM_BLOCKS){
        if(m_cacheDir[i] != nullptr){
            int counterData = m_algorithm == ALGORITHM_LRU ? int(m_cacheDir[i]->lruCounter) : int(m_cacheDir[i]->fifoCounter);
            cout << setw(8) << int(m_cacheDir[i]->blMc) << setw(8)
                    << setw(11) << int(m_cacheDir[i]->setId) << setw(9)
                    << setw(8) << int(m_cacheDir[i]->tag) << setw(9)
                    << setw(14) << int(m_cacheDir[i]->blMp) << setw(9)
                    << setw(12) << int(counterData) << setw(9)
                    << setw(8) << int(m_cacheDir[i]->dirty) << setw(9)
                    << setw(8) << int(m_cacheDir[i]->replaced)<< endl;
        }

        i++;
    }
}