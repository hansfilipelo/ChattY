/*
FILNAMN: 		User.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-14
BESKRIVNING:	
*/

#include "../room/room.h"
using namespace std;

User::~User(){
    parentRoom->removeRoom(this);
    parentRoom = nullptr;
    masterPointer = nullptr;
}

// ----------------------------------

void User::chooseRoom(Room* newRoom){
    newRoom->addRoom(this);
    if(this->parentRoom != nullptr){
        cout << "chooseRoom" << endl;
		parentRoom->removeRoom(this);
	}
    this->parentRoom = newRoom;
}

// ----------------------------------

void User::receiveMessage(Message inMessage){
    log.push_back(inMessage); //tbd
}

// ----------------------------------

void User::sendMessage(Message outMessage){
    cout << "Skickad fr user" << endl;
    parentRoom->receiveMessage(outMessage);
    log.push_back(outMessage);
}

// ----------------------------------

void User::initRoom(string name){
    parentRoom->addRoom(masterPointer->createRoom(name));
}