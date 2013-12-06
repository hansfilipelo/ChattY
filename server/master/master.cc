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
    removeRoom("root");
    
    topRoom = nullptr;
}

// ---------------------------------------

unsigned int Master::getPosOfRoom(string name){
    
    unsigned int p = this->rooms.size(); // <--- this line segfaults. WAI?!
    for( unsigned int i = 0 ; i < p ; i++) {
        if(this->rooms.at(i)->getName() == name){
            return i;
        }
    }
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
        rooms.push_back(temp);
        return temp;
    }
    throw logic_error("Trying to create room, but name is taken (Liam Neeson)");
}

// ---------------------------------------

void Master::removeRoom(string name) {
    unsigned int pos = getPosOfRoom(name);
    delete rooms.at(pos);
    rooms.erase(rooms.begin() + pos);
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
        
        rooms.push_back(temp);
        
        cout << name <<" was connected!" <<endl;
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
    for( unsigned int i = 0 ; i < rooms.size() ; i++) {
        if(rooms.at(i)->getName() == name){
            return rooms.at(i);
        }
    }
    throw logic_error("Trying to find room that does not exist");
}

//----------------------------------------------

void Master::printVector(){
    for( unsigned int i = 0 ; i < rooms.size() ; i++) {
        cout << rooms.at(i)->getName() << endl;
    }
}