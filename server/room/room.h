/*
FILNAMN: 		room.h
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-14
BESKRIVNING:	
Benny
*/

#ifndef room_H
#define room_H

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stdexcept>
#include "../getTime.h"
#include "../message/message.h"
#include "../master/master.h"

class Room {
public:
    // Construct
    Room(std::string,class Master*);
    // Destruct
    virtual ~Room();
    
    virtual void sendMessage(Message);
    void createRoom(std::string);
    void addRoom(Room*);
    void removeRoom(Room*);             // Throws error if room doesn't exist
    void receiveMessage(Message);
    std::string getName();
    friend void destructHelp(Room*);
    Room* getRoom(std::string);
    Message getMessage(int i);
    
protected:
    void saveToFile(Message);
    void sendMessageAll(Message);
    std::string name;
    std::map<std::string,Room*> rooms;
    std::vector<Message> log;
    Room* parentRoom = nullptr;
    Master* masterPointer = nullptr;
    

};

// --------------------
// User

class User : public Room
{
public:
    User(std::string inName, Master* master) : Room(inName,master) {};
    ~User();
//    std::string name;
    void sendMessage(Message);
    void receiveMessage(Message);
    void chooseRoom(Room*);
    void initRoom(std::string);
    Message getMessage(int i);

    
private:
    std::vector<Message> log;
    Room* parentRoom;
    
};

#endif
