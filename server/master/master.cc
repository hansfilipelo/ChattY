/*
 FILNAMN: 		master.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-14
 BESKRIVNING:
 */

#include "master.h"

using namespace std;

// ---------------------------------------
// Constructor

Master::Master() {
    topRoom = new Room("root",this);
    rooms.push_back(topRoom);
}

// ---------------------------------------
// Destructor

Master::~Master() {
    cout << "Hello1" << endl;
    delete topRoom;
    cout << "Hello" << endl;
    rooms.clear();
    topRoom = nullptr;
}

// ---------------------------------------

unsigned int Master::getPosOfRoom(string name){
    for( unsigned int i = 0 ; i < rooms.size() ; i++) {
        if(rooms.at(i)->getName() == name){
            return i;
        }
    }
    throw logic_error("No such room in Rooms");
    return 0;
}



// ---------------------------------------

Room* Master::createRoom(string name) {
    if ( not(getRoom(name)) ) {
        throw logic_error{"Already room by that name"};
    }
    Room* temp = new Room(name,this);
    rooms.push_back(temp);
    return temp;
}

// ---------------------------------------

void Master::removeRoom(string name) {
    if ( getRoom(name) != nullptr ) {
        delete getRoom(name);
        cout << name << " was removed in master" << endl;
        cout << getTop()->getName() << endl;
        rooms.erase(rooms.begin() + getPosOfRoom(name));
    }
    else {
        throw logic_error{"There's no room by that name"};
    }
}


// ---------------------------------------

void Master::removeUser(string name){
    removeRoom(name);
}

// ---------------------------------------

void Master::createUser(string name){
    if ( getRoom(name) != nullptr ) {
        throw logic_error{"Already user by that name"};
    }
    User* temp = new User(name,this);
    
    Room* roomTemp = dynamic_cast<Room*>(temp);
    
    temp->chooseRoom(topRoom);
    
    rooms.push_back(roomTemp);
    return;
}

//----------------------------------------------

Room* Master::getTop(){
    return topRoom;
}

//----------------------------------------------

Room* Master::getRoom(std::string name){
    for( unsigned int i = 0 ; i < rooms.size() ; i++) {
        if(rooms.at(i)->getName() == name){
            return rooms.at(i);
        }
    }
    throw logic_error("Trying to find room that does not exist");
}