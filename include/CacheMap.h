//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_CACHEMAP_H
#define CACHESIM_CACHEMAP_H

#define CACHE_NUM_BLOCKS 8
//#define DEBUG

/**
 * Fichero encargado de representar la memoria.
 */


typedef struct {
    int blMp;
    int blMc;
    int tag;
    bool lru;
    bool free;
} Block;

/**
 * Matriz de punteros a blocks
 */
class CacheMap {

public:
    CacheMap(int setSize);

    bool addrCheckByDirect(int tag, int blMp, int blMc);
    bool addrCheckBySetAssoc(int tag, int blMp, int setId);
    bool addrCheckByTotAssoc(int blMp);

    void display();

private:
    Block* m_cacheDir[CACHE_NUM_BLOCKS];
};

#endif //CACHESIM_CACHEMAP_H