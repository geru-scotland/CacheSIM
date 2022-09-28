//
// Created by Basajaun on 28/9/22.
//
#include <iostream>
#include "DataMgr.h"

using namespace std;


int DataMgr::m_wordsPerBlock ;
int DataMgr::m_totalCicles;
int DataMgr::m_hits;
int DataMgr::m_accesses;
CacheFlags DataMgr::m_status;

void DataMgr::Init(int wordsPerBlock){
    m_wordsPerBlock = wordsPerBlock;
    m_totalCicles = 0;
    m_hits = 0;
    m_accesses = 0;
    m_status = CACHE_FLAG_NONE;
}

void DataMgr::ResetStatus(){
    m_status = CACHE_FLAG_NONE;
}

/**
 * Tmc = 2c
 * Tmp = 21c
 * Tbuff = 1c
 *
 * Acierto: Tmc
 *
 * Ttb: Tmp + (palabras/bloque -1)*Ttbuff
 * Fallo SIN reemplazo: Tmc + Ttb
 * Fallo CON reemplazo: Tmc + 2Ttb
 */
void DataMgr::computeOpTime(bool hit) {
    int opCicles = 0;

    if(!hit){
        if(m_status == CACHE_FLAG_REPLACED)
            opCicles = VALUE_TMC + 2*(VALUE_TMP + (m_wordsPerBlock - 1)*VALUE_TBUFF);
        else
            opCicles = VALUE_TMC + (VALUE_TMP + (m_wordsPerBlock - 1)*VALUE_TBUFF);
    }else{
        m_hits++;
        opCicles = VALUE_TMC;
    }

    m_totalCicles += opCicles;
    displayOpResult(hit, opCicles);
}

void DataMgr::displayOpResult(bool hit, int cicles) {
    string result = "";
    hit ? result = "[HIT] " : result = "[MISS] ";
    m_status == CACHE_FLAG_REPLACED ? result.append("[REPLACEMENT]") : result.append("");

    cout << result << " Cicles: "<< cicles << endl;
}

void DataMgr::setLastOpStatus(CacheFlags flags) {
    m_status = flags;
}

void DataMgr::increaseAccesses() {
    m_accesses++;
}

int DataMgr::getTotalCicles() {
    return m_totalCicles;
}

float DataMgr::getHitRate() {
    return float(m_hits)/float(m_accesses);
}