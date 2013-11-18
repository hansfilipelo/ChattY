/*
FILNAMN: 		User.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-14
BESKRIVNING:	
*/

#include "../room/room.h"
using namespace std;

User::~User(){
    parentRoom->removeRoom(*this); //you sure? *this eller this&?
}

void User::chooseRoom(Room* newRoom){
    newRoom->addRoom(*this);
    parentRoom = newRoom;
}

void User::receiveMessage(Message inMessage){
    log.push_back(inMessage); //tbd
}

void User::sendMessage(Message outMessage){
    parentRoom->receiveMessage(outMessage);
}

void User::initRoom(string name){
    parentRoom->addRoom(masterPointer->createRoom(name));
}