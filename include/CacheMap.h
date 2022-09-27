//
// Created by Basajaun on 27/9/22.
//

#ifndef CACHESIM_CACHEMAP_H
#define CACHESIM_CACHEMAP_H


/**
 * Fichero encargado de representar la memoria.
 */

struct Word {

};

struct Block {
    int id;
    bool lru;
    Word* words[]; // Revisar esto. Crear un init del simulator en base a los params de entrada y que se cree un vector o array de punteros en consecuencia.
};

/**
 * Matriz de punteros a blocks
 */
class CacheMap {

public:
    CacheMap();

private:

};

#endif //CACHESIM_CACHEMAP_H