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
#include <QReadWriteLock>
#include "../getTime.h"
#include "../room/room.h"

/*
 Master class. Class that is running the back end of the server, creating and controlling users and rooms.
 
 */

class Master {
public:
    Master();
    ~Master();
    
    // Rooms
    class Room* createRoom(std::string);
    void removeRoom(std::string);
    Room* getRoom(std::string);
    Room* getTop();
    
    // Users (subclass of rooms)
    class User* createUser(std::string);
    void removeUser(std::string);
    
    void updateStructForAll(); // Send info regarding users / rooms to all clients
    
    void printVector(); // testing purposes 
    
protected:
    bool userOrNot(Room* inRoom);

    unsigned int getPosOfRoom(std::string);
    std::vector<Room*> rooms;
    Room* topRoom;

    QReadWriteLock roomLock;
};

#endif
