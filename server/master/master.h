/*
FILNAMN: 		master.h
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-14
BESKRIVNING:	
*/

#ifndef master_H
#define master_H

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "../getTime.h"
#include "../room/room.h"

class Master {
public:
    Master();
    ~Master();
    
    Room* createRoom(std::string);
    void removeRoom(std::string);
    Room* createUser(std::string);
    void removeUser(std::string);
    
    
protected:
    std::map<std::string, Room*> rooms;
    Room* topRoom;
};

#endif