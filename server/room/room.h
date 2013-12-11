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
    
    virtual void receiveMessage(Message);
    virtual void sendMessage(Message);
    
    virtual void requestStruct();
    
    void createRoom(std::string);
    void addRoom(Room*);
    void removeRoom(Room*); // Throws error if room doesn't exist
    
    std::string getName();
    Room* getParentRoom();
    virtual std::vector<std::string> getStruct();
    void listUsers();
    void listRooms();
    Room* getRoom(std::string);
    Message getMessage(unsigned int i);
    
    virtual void chooseRoom(Room*);
    std::vector<Message> log;
    
protected:
    friend void throwUp(Room* inRoom);
    friend void ifRoomRemove(Room* inRoom);
    unsigned int getPosOfRoom(std::string name) const;
    void saveToFile(Message);
    void readAllFromFile();
    void sendMessageAll(Message);
    
    std::string name;
    std::vector<Room*> rooms;
    Room* parentRoom = nullptr;
    Master* masterPointer = nullptr;
};

// --------------------
// User

class Thread;

class User : public Room
{
public:
    User(std::string inName, Master* master) : Room(inName,master) {};
    ~User();
    std::string name;
    void sendMessage(Message);
    void receiveMessage(Message);
    
    void sendHistory();
    void chooseRoom(Room*);
    void initRoom(std::string);
    void setThread(Thread*);
    std::vector<std::string> getStruct();
    void requestStruct();
    
protected:
    Thread* thread;
    
};

#endif
