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
    cout << "** CACHESIM v.05 **" << endl;
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
        cout << "Introduce word size (4 or 8 bytes): ";
        cin >> wordSize;
    }

    while(blockSize!= 32 && blockSize!= 64) {
        cout << "Introduce block size (32 or 64 bytes): ";
        cin >> blockSize;
    }

    while(setSize!= 1 && setSize!= 2 && setSize!= 4 && setSize!= 8) {
        cout << "Introduce set size (1 (direct), 2, 4 u 8 (totally assoc): ";
        cin >> setSize;
    }

    while(replaceAlgorithm != 0 && replaceAlgorithm!= 1) {
        cout << "Introduce a replacement algorithm 0 (FIFO) - 1 (LRU): ";
        cin >> replaceAlgorithm;
    }
    cMgr->setConfig(wordSize, blockSize, setSize, replaceAlgorithm);
    DataMgr::Init(blockSize/wordSize);
}

int16_t Simulator::newAddress() {

    int16_t addr = 0;
    int opcode = -1;
    cout << "Address: ";
    cin >> addr;

    if(addr != -1)
    {
        while(opcode != 0 && opcode!= 1) {
            cout << "Operation(0 ld, 1 st): ";
            cin >> opcode;
            cout << endl;
        }
        cMgr->manageNewOperation(addr, (bool)opcode);
    }

    return addr;
}
