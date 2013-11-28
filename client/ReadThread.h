/*
FILNAMN: 		readThread.h
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-28
BESKRIVNING:	
*/

#ifndef ReadThread_H
#define ReadThread_H

#include <QtCore>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "NetClient.h"

class ReadThread : public QThread {
public:
    ReadThread(NetClient*,std::string);
    void run();
    
protected:
    NetClient* client;
    std::string name;
};

#endif
