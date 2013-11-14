/*
FILNAMN: 		User.cc
LABORATION:		
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
DATUM:			2013-11-14
BESKRIVNING:	
*/

#include <User.h>
using namespace std;

User::User(string inName){
    name = InName;
}

User::~User(){
    parentRoom->removeRoom(this&); //you sure? *this eller this&?
}

User::chooseRoom(Room* newRoom){
    newRoom->addRoom(this);
    parentRoom = newRoom;
}

User::recieveMessage(Message inMessage){
    log.push_back(inMessage); //tbd
}

User::sendMessage(Message outMessage){
    parentRoom->recieveMessage(outMessage);
}