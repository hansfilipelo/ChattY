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
    topRoom = new Room("root");
    rooms.insert(pair<string,Room*>(topRoom->getName(), topRoom));
}

// ---------------------------------------
// Destructor

Master::~Master() {
    for (auto i = rooms.cbegin(); i != rooms.cend(); ++i) {
        delete i->second;
    }
    rooms.clear();
    topRoom = nullptr;
}

// ---------------------------------------

Room* Master::createRoom(string name) {
    Room* temp = new Room(name);
    rooms.insert(pair<string,Room*>(temp->getName(),temp));
    return temp;
}

// ---------------------------------------

void Master::removeRoom(string name) {
    if ( rooms.find(name) != rooms.cend() ) {
        delete rooms.find(name)->second;
        rooms.erase(rooms.find(name));
    }
    else {
        throw logic_error{"There's no room by that name"};
    }
}

// ---------------------------------------

void Master::removeUser(string name){
    removeRoom(name);
}

