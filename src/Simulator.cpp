//
// Created by Basajaun on 27/9/22.
//
#include <iostream>
#include "Simulator.h"
#include "CacheMgr.h"
#include "DataMgr.h"

using namespace std;

Simulator::Simulator() {
    cMgr = new CacheMgr();
}


void Simulator::initConfig(){

    int wordSize = 0;
    int blockSize = 0;
    int setSize = 0;
    int replaceAlgorithm = -1;

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
    while(wordSize != 4 && wordSize != 8){
        cout << "Introduce el tamaño de la palabra (4 u 8 bytes): ";
        cin >> wordSize;
        cout << endl;
    }

    while(blockSize!= 32 && blockSize!= 64) {
        cout << "Introduce el tamaño del Bloque (32 o 64 bytes): ";
        cin >> blockSize;
        cout << endl;
    }

    while(setSize!= 1 && setSize!= 2 && setSize!= 4 && setSize!= 8) {
        cout << "Introduce el tamaño del conjunto (1 (directa), 2, 4 u 8 (totalmente asociativa): ";
        cin >> setSize;
        cout << endl;
    }

    while(replaceAlgorithm != 0 && replaceAlgorithm!= 1) {
        cout << "Introduce el algoritmo de reemplazo: 0 (FIFO) - 1 (LRU): ";
        cin >> replaceAlgorithm;
        cout << endl;
    }
    cMgr->setConfig(wordSize, blockSize, setSize, replaceAlgorithm);
    DataMgr::Init(blockSize/wordSize);
}

int16_t Simulator::newAddress() {

    int16_t addr = 0;
    int opcode = -1;
    cout << "Dirección de memoria: ";
    cin >> addr;
    cout << endl;

    if(addr != -1)
    {
        while(opcode != 0 && opcode!= 1) {
            cout << "Operación (0 ld, 1 st): ";
            cin >> opcode;
            cout << endl;
        }
        cMgr->manageNewOperation(addr, (bool)opcode);
    }

    return addr;
}
