/*
 FILNAMN: 		master.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-14
 BESKRIVNING:
 */

#include "master.h"

using namespace std;

//----------------------------------------
// Helper function

bool Master::userOrNot(Room* inRoom) {
    User* userTemp = dynamic_cast<User*>(inRoom);
    
    if (userTemp == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

// ------------------------


// ---------------------------------------
// Constructor

Master::Master() {
    topRoom = new Room("root",this);
    rooms.push_back(topRoom);
}

// ---------------------------------------
// Destructor

Master::~Master() {
    removeRoom("root");
    
    topRoom = nullptr;
}

// ---------------------------------------

unsigned int Master::getPosOfRoom(string name){
    
    roomLock.lockForRead();
    unsigned int p = this->rooms.size(); // <--- this line segfaults. WAI?!
    for( unsigned int i = 0 ; i < p ; i++) {
        if(this->rooms.at(i)->getName() == name){
            roomLock.unlock();
            return i;
        }
    }
    roomLock.unlock();
    throw logic_error("No such room in Rooms");
    return 0;
}



// ---------------------------------------

Room* Master::createRoom(string name) {
    try{
        getRoom(name);
    }
    catch(...){
        Room* temp = new Room(name,this);
        roomLock.lockForWrite();
        rooms.push_back(temp);
        roomLock.unlock();
        
        roomLock.lockForRead();
        // Update structure on all clients
        for (unsigned int i = 0; i < rooms.size(); i++) {
            if ( userOrNot(rooms.at(i)) ) {
                rooms.at(i)->requestStruct();
            }
        }
        roomLock.unlock();
        
        return temp;
    }
    throw logic_error("Trying to create room, but name is taken (Liam Neeson)");
}

// ---------------------------------------

void Master::removeRoom(string name) {
    unsigned int pos = getPosOfRoom(name);
    roomLock.lockForWrite();
    delete rooms.at(pos);
    rooms.erase(rooms.begin() + pos);
    roomLock.unlock();
}


// ---------------------------------------

void Master::removeUser(string name){
    removeRoom(name);
}

// ---------------------------------------

User* Master::createUser(string name){
    try {
        getRoom(name);
    } catch (...) {
        User* temp = new User(name,this);
        temp->chooseRoom(topRoom);
        
        roomLock.lockForWrite();
        rooms.push_back(temp);
        roomLock.unlock();

        // Update structure on all clients
        roomLock.lockForRead();
        for (unsigned int i = 0; i < rooms.size(); i++) {
            if ( rooms.at(i)->getName() != name and userOrNot(rooms.at(i)) ) {
                rooms.at(i)->requestStruct();
            }
        }
        roomLock.unlock();
        return temp;
    }
    
    throw logic_error{"Already user by that name"};
}

//----------------------------------------------

Room* Master::getTop(){
    return topRoom;
}

//----------------------------------------------

Room* Master::getRoom(string name){

    roomLock.lockForRead();

    for( unsigned int i = 0 ; i < rooms.size() ; i++) {
        if(rooms.at(i)->getName() == name){
            roomLock.unlock();
            return rooms.at(i);
        }
    }
    roomLock.unlock();
    throw logic_error("Trying to find room that does not exist");
}

//----------------------------------------------

void Master::printVector(){
    roomLock.lockForRead();
    for( unsigned int i = 0 ; i < rooms.size() ; i++) {
        cout << rooms.at(i)->getName() << endl;
    }
    roomLock.unlock();
}

// ---------------------------------------------

void Master::updateStructForAll() {
    roomLock.lockForRead();
    for (unsigned int i = 0; i < rooms.size(); i++) {
        
        if ( userOrNot(rooms.at(i)) ) {
            rooms.at(i)->requestStruct();
        }
    }
    roomLock.unlock();
}




