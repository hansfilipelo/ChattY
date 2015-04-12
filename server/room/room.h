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
#include <QDir>
#include <QDate>
#include <QString>
#include <QReadWriteLock>
#include "../getTime.h"
#include "../message/message.h"
#include "../master/master.h"

class Room {
public:
    // Construct
    Room(std::string,class Master*,class Master*);
    Room(std::string,class Master*);
    // Destruct
    virtual ~Room();
    
    // Sending 'n receiving
    virtual void receiveMessage(Message);
    virtual void sendMessage(Message);
    
    // Related to logging
    virtual void setFilePath();
    virtual void readAllFromFile();
    std::vector<Message> readOldFromFile(unsigned int);
    
    // Relating to rooms
    void createRoom(std::string);
    void addRoom(Room*);
    void removeRoom(Room*); // Throws error if room doesn't exist
    virtual void chooseRoom(Room*); // Useless on Room, only for subclass User
    
    // Accessor funcitons
    std::string getName();
    Room* getParentRoom();
    Room* getRoom(std::string);
    Message getMessage(unsigned int i);
    virtual std::vector<std::string> getStruct();
    virtual void requestStruct();
    void listUsers();
    void listRooms();
    
    // Rooms message log
    std::vector<Message> log;
    
protected:
    
    // Internal helper functions
    friend void throwUp(Room* inRoom);
    friend void ifRoomRemove(Room* inRoom);
    unsigned int getPosOfRoom(std::string name) const;
    void saveToFile(Message);
    void sendMessageAll(Message);
    
    
    std::string filepath="";
    std::string date="";
    std::string name;
    
    // Pointers for structuring
    std::vector<Room*> rooms;
    Room* parentRoom = nullptr;
    Master* masterPointer = nullptr;

    // Read-write lock
    QReadWriteLock msgQueueLock;
};

// --------------------
// User

class Thread;

class User : public Room
{
public:
    User(std::string inName, Master* master) : Room(inName,master,nullptr) {};
    ~User();
    std::string name;
    void sendMessage(Message);
    void receiveMessage(Message);
    
    void setFilePath();
    void readAllFromFile();
    void chooseRoom(Room*);
    void initRoom(std::string);
    void setThread(Thread*);
    std::vector<std::string> getStruct();
    void requestStruct();
    
protected:
    Thread* thread;
    
};

#endif
