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
