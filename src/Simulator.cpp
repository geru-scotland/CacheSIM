//
// Created by Basajaun on 27/9/22.
//
#include <iostream>
#include "Simulator.h"
#include "CacheMgr.h"
using namespace std;

Simulator::Simulator() {
    cm = new CacheMgr();
}


void Simulator::initConfig(){

    int16_t wordSize;
    int16_t blockSize;
    int8_t setSize;
    int8_t replaceAlgorithm;

    cout << endl;
    cout << endl;
    cout << "*******************" << endl;
    cout << "** CACHESIM v.01 **" << endl;
    cout << "*******************" << endl;
    cout << endl;
    cout << endl;
    cout << "INITIAL DATA SET: " << endl;
    cout << "-----------------" << endl;
    cout << endl;

    /*
     * Data
     */
    cout << "Introduce el tamaño de la palabra (4 u 8 bytes):";
    cin >> wordSize;
    cout << endl;

    cout << "Introduce el tamaño del Bloque (32 o 64 bytes):";
    cin >> blockSize;
    cout << endl;

    cout << "Introduce el tamaño del conjunto (1 (directa), 2, 4 u 8 (totalmente asociativa):";
    cin >> setSize;
    cout << endl;

    cout << "Introduce el algoritmo de reemplazo: 0 (FIFO) - 1 (LRU):";
    cin >> replaceAlgorithm;
    cout << endl;

    cm->setConfig(wordSize, blockSize, setSize, replaceAlgorithm);

    cout << "Tamaño de palabra elegido: " << cm->getWordSize() << endl;
}

int16_t Simulator::manageNewAddress() {

    int16_t addr = 0;
    bool opcode = 0;
    cout << "Dirección de memoria:";
    cin >> addr;
    cout << endl;
    cout << "Operación (0 ld, 1 st): ";
    cin >> opcode;
    cout << endl;
    if(addr != -1)
        cm->manageNewOperation();
    return addr;
}
