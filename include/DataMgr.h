//
// Created by Basajaun on 28/9/22.
//

#ifndef CACHESIM_DATAMGR_H
#define CACHESIM_DATAMGR_H

#include "SharedDefines.h"

enum AccessValues {
    VALUE_TMC   = 2,
    VALUE_TMP   = 21,
    VALUE_TBUFF = 1,
};

class DataMgr {
public:
    static void Init(int wordsPerBlock);
    static void ResetStatus();

    static void computeOpTime(bool hit);
    static void displayOpResult(bool hit, int cicles);

    static void setLastOpStatus(CacheFlags flags);

    static void increaseAccesses();

    static int getTotalCicles();
    static float getHitRate();

    static int m_wordsPerBlock;
    static int m_totalCicles;
    static int m_hits;
    static int m_accesses;
    static CacheFlags m_status;
};


#endif //CACHESIM_DATAMGR_H
