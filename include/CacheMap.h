//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_CACHEMAP_H
#define CACHESIM_CACHEMAP_H

#define CACHE_NUM_BLOCKS 8

/**
 * Fichero encargado de representar la memoria.
 */


struct Block {
    int id;
    int tag;
    bool lru;
};

/**
 * Matriz de punteros a blocks
 */
class CacheMap {

public:
    CacheMap();

private:
    Block* dir[CACHE_NUM_BLOCKS];
};

#endif //CACHESIM_CACHEMAP_H