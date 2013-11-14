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

void Room::sendMessage(message inMessage) {
    string to = inMessage.to;
    
    if ( rooms.find(to) == rooms.end() ) {
        message errorMessage("User does not exist", name, inMessage.from, getCurrentDateTime());
        rooms.at(to).receiveMessage(errorMessage);
    }
    
    User* userTemp = dynamic_cast<User*>(&rooms.at(to));
    
    if ( userTemp == nullptr) {
        message errorMessage("You can't a send whisper to a room, dummy!", name, inMessage.from, getCurrentDateTime());
        rooms.at(to).receiveMessage(errorMessage);
    }
    else {
        rooms.at(to).receiveMessage(inMessage);
    }
}

// ----------------------------------

void Room::receiveMessage(message inMessage) {
    string to = inMessage.to;
    if(to == name){
        sendMessageAll(inMessage);
    }
    else{
        sendMessage(inMessage);
    }
}

// ----------------------------------

void Room::sendMessageAll(message inMessage) {
    for (unsigned int i = 0; i < rooms.length(); i++) {
        User* userTemp = dynamic_cast<User*>(&rooms.at(to));
        if ( usertemp == nullptr ) {
            continue;
        }
        rooms.at(to).receiveMessage(inMessage);
    }
}

// ----------------------------------

void Room::addRoom(Room& inRoom) {
    rooms.insert(inRoom.name, &inRoom);
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



