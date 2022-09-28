//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_SHAREDDEFINES_H
#define CACHESIM_SHAREDDEFINES_H

#define CACHE_NUM_BLOCKS 8
//#define DEBUG

enum CorrespAssoc{
    ASSOC_DIRECT = 1,
    ASSOC_SET_2 = 2,
    ASSOC_SET_4 = 4,
    ASSOC_TOTAL = CACHE_NUM_BLOCKS
};

enum ReplacementAlgorithms {
    ALGORITHM_FIFO = 0,
    ALGORITHM_LRU
};

enum OPcodes{
    OPCODE_READ = 0,
    OPCODE_WRITE
};

enum CacheFlags {
    CACHE_FLAG_NONE = 0,
    CACHE_FLAG_DIRTY = 1,
    CACHE_FLAG_REPLACED = 2,
    CACHE_FLAG_FREE = 4,
};

enum DisplayMode {
    DISPLAY_DIRECT = 0,
    DISPLAY_TOTAL_ASOC,
    DISPLAY_SET_ASOC
};

/*
 * Funciones auxiliares sobre las que se generarán punteros para poder ser pasadas
 * como parámetros.
 */
inline void compareDesc(int counter, int& cmp, int& cachePos, int i = 0) {
    if(counter < cmp){
        cmp = counter;
        cachePos = i;
    }
}

inline void compareAsc(int counter, int& cmp, int& cachePos, int i = 0) {
    if(counter > cmp){
        cmp = counter;
        cachePos = i;
    }
}

#endif //CACHESIM_SHAREDDEFINES_H
