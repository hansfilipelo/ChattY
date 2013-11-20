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
    rooms.insert(pair<string,Room*>(topRoom->getName(), topRoom));
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

Room* Master::createRoom(string name) {
    if ( rooms.find(name) != rooms.cend() ) {
        throw logic_error{"Already room by that name"};
    }
    Room* temp = new Room(name,this);
    rooms.insert(pair<string,Room*>(temp->getName(),temp));
    return temp;
}

// ---------------------------------------

void Master::removeRoom(string name) {
    if ( rooms.find(name) != rooms.cend() ) {
        delete rooms.find(name)->second;
        cout << name << " was removed in master" << endl;
        cout << getTop()->getName() << endl;
        rooms.erase(name);
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

Room* Master::createUser(string name){
    if ( rooms.find(name) != rooms.cend() ) {
        throw logic_error{"Already user by that name"};
    }
    User* temp = new User(name,this);
    
    Room* roomTemp = dynamic_cast<Room*>(temp);
    
    rooms.insert(pair<string,Room*>(roomTemp->getName(),roomTemp));
    return roomTemp;
}

//----------------------------------------------

Room* Master::getRoom(std::string name){
    if(rooms.find(name) == rooms.end()){
        cout << "Not known room" << endl;
    }
	return rooms.find(name)->second;
}

Room* Master::getTop(){
    return topRoom;
}
