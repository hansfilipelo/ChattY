/*
FILNAMN: 		room.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-14
BESKRIVNING:	
*/

#include "room.h"

using namespace std;

// ----------------------------------
// Constructor

Room::Room(string inName) {
    name = inName;
}

// ----------------------------------
// Destructor

Room::~Room() {
    for (auto i = rooms.cbegin(); i != rooms.cend(); ++i) {
        User* userTemp = dynamic_cast<User*>(i->second);
        if ( userTemp == nullptr ) {
            delete i->second;
        }
        else if ( parentRoom != nullptr ) {
            parentRoom->addRoom(*i->second);
            this->removeRoom(*i->second);
        }
    }
}

// ----------------------------------

void Room::sendMessage(Message inMessage) {
    string to = inMessage.getTo();
    
    if ( rooms.find(to) == rooms.end() ) {
        Message errorMessage("User does not exist", name, inMessage.getFrom());
        rooms.at(to)->receiveMessage(errorMessage);
    }
    
    User* userTemp = dynamic_cast<User*>(rooms.at(to));
    
    if ( userTemp == nullptr) {
        Message errorMessage("You can't a send whisper to a room, dummy!", name, inMessage.getFrom());
        rooms.at(to)->receiveMessage(errorMessage);
    }
    else {
        rooms.at(to)->receiveMessage(inMessage);
    }
}

// ----------------------------------

void Room::receiveMessage(Message inMessage) {
    string to = inMessage.getTo();
    if(to == name){
        sendMessageAll(inMessage);
        saveToFile(inMessage);
    }
    else{
        sendMessage(inMessage);
    }
}

// ----------------------------------

void Room::sendMessageAll(Message inMessage) {
    string to = inMessage.getTo();
    
    for (unsigned int i = 0; i < rooms.size(); i++) {
        User* userTemp = dynamic_cast<User*>(rooms.at(to));
        if ( userTemp == nullptr ) {
            continue;
        }
        rooms.at(to)->receiveMessage(inMessage);
    }
}

// ----------------------------------

void Room::addRoom(Room& inRoom) {
    inRoom.parentRoom = this;
    rooms.insert(pair<string, Room*>(inRoom.name,&inRoom));
}

// ----------------------------------

void Room::removeRoom(Room& inRoom) {
    if ( rooms.find(inRoom.name) == rooms.end() ) {
        throw logic_error{"Trying to remove room that's not in this parent room"};
    }
    else {
        rooms.erase(rooms.find(inRoom.name));
    }
}

// ----------------------------------

void Room::saveToFile(Message inMessage) {
    cout << inMessage.getMessage() << endl;
    return;
}

// ------------------------------------

string Room::getName() {
    return name;
}

