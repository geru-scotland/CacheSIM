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
int DataMgr::data[MAX_STORED_DATA];

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

void DataMgr::storeResultData(int blMc, int blMpPrev, int blMpNew, int dirty, int opcode) {
    data[DATA_CACHE_BLOCK] = blMc;
    data[DATA_MP_BLOCK] = blMpPrev;
    data[DATA_MP_NEW] = blMpNew;
    data[DATA_DIRTY] = dirty;
    data[DATA_OPCODE] = opcode;
}

/**
 * Cálculo de ciclos
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

/**
 * Volcado de información sobre la última instrucción.
 */
void DataMgr::displayOpResult(bool hit, int cicles) {
    cout << "______________________________________________________" << endl;
    cout << "______________________________________________________" << endl;
    if(hit){
        cout  << "\033[1;32m[HIT]\033[0m" << " Found block " << data[DATA_MP_BLOCK] << " in Cache position " << data[DATA_CACHE_BLOCK];
        if(data[DATA_OPCODE] == OPCODE_WRITE)
            cout << " (WRITE)";
        cout << endl;
    }else{
        if(m_status == CACHE_FLAG_REPLACED){
            cout << "\033[1;31m[MISS]\033[0m"<<"\033[1;33m[REPLACEMENT]\033[0m";
            if(data[DATA_DIRTY]){
                cout << " Block " << data[DATA_MP_BLOCK] << " in Cache position "<< data[DATA_CACHE_BLOCK] <<" was dirty -> transferring it to buffer." << endl;
                cout << "\033[1;35m[OVERRIDE]\033[0m"<<" New block: " << data[DATA_MP_NEW];
            }else
                cout << "Replacing block "<< data[DATA_MP_BLOCK] <<" (not dirty) with New block: " << data[DATA_MP_NEW] << " in Cache position: "<< data[DATA_CACHE_BLOCK];
        } else{
            cout << "\033[1;31m[MISS]\033[0m" << " Block "<< data[DATA_MP_NEW] <<" not found in Cache. Inserting it into a free cache position: " << data[DATA_CACHE_BLOCK];
        }
    }
    cout << endl;
    cout <<"[TIME] Cicles: "<< cicles << endl;
}

void DataMgr::setLastOpStatus(CacheFlags flags) { m_status = flags; }

void DataMgr::increaseAccesses() { m_accesses++; }

int DataMgr::getTotalCicles() { return m_totalCicles; }

int DataMgr::getTotalAccesses() { return m_accesses; }

int DataMgr::getTotalHits() { return m_hits;}

float DataMgr::getHitRate() {
    return float(m_hits)/float(m_accesses);
}