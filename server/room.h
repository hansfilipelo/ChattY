/*
FILNAMN: 		room.h
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-14
BESKRIVNING:	
*/

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "message.h"

class Room {
public:
    // Construct
    Room(string);
    
    void sendMessage(message*);
    void addRoom(Room&);
    void removeRoom(Room&);
    void receiveMessage;
    
protected:
    std::string name;
    std::map<string,room*> rooms;
    std::vector<message*> log;
};
