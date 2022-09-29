//
// Created by Basajaun on 28/9/22.
//

#ifndef CACHESIM_DATAMGR_H
#define CACHESIM_DATAMGR_H

#include "SharedDefines.h"
#define MAX_STORED_DATA 5

enum AccessValues {
    VALUE_TMC   = 2,
    VALUE_TMP   = 21,
    VALUE_TBUFF = 1,
};

enum StoredData {
    DATA_CACHE_BLOCK = 0,
    DATA_MP_BLOCK,
    DATA_MP_NEW,
    DATA_DIRTY,
    DATA_OPCODE
};

/**
 * Clase estática encargada de gestionar las diferentes
 * estadísticas de la simulación.
 */
class DataMgr {
public:
    static void Init(int wordsPerBlock);
    static void ResetStatus();

    static void storeResultData(int blMc = -1, int blMpPrev= -1, int blMpNew = -1, int dirty = 0, int opcode = 0);
    static void computeOpTime(bool hit);
    static void displayOpResult(bool hit, int cicles);

    static void setLastOpStatus(CacheFlags flags);

    static void increaseAccesses();

    static int getTotalCicles();
    static int getTotalAccesses();
    static int getTotalHits();
    static float getHitRate();

    static int m_wordsPerBlock;
    static int m_totalCicles;
    static int m_hits;
    static int m_accesses;
    static CacheFlags m_status;

    static int data[MAX_STORED_DATA];
};


#endif //CACHESIM_DATAMGR_H
