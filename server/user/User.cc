/*
FILNAMN: 		User.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-14
BESKRIVNING:	
*/

#include "../room/room.h"
using namespace std;

User::~User(){
    parentRoom->removeRoom(this); //you sure? *this eller this&?
}

void User::chooseRoom(Room* newRoom){
    newRoom->addRoom(this);
    if(parentRoom != nullptr){
		parentRoom->removeRoom(this);
	}
    parentRoom = newRoom;
    
}

void User::receiveMessage(Message inMessage){
    log.push_back(inMessage); //tbd
}

void User::sendMessage(Message outMessage){
    parentRoom->receiveMessage(outMessage);
    log.push_back(outMessage);
}

void User::initRoom(string name){
    parentRoom->addRoom(masterPointer->createRoom(name));
}

Message User::getMessage(int i){
	 if (log.size() < i){
		 throw logic_error{"No message at that position!"};
	 }
	 return log[i];
 }
