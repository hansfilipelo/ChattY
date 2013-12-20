/*
FILNAMN: 		User.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-14
BESKRIVNING:	
*/

#include "../room/room.h"
#include "../serverclass/thread.h"

using namespace std;

/*
 User class. Issues commands from user and holds information about user.
 */

User::~User(){
    parentRoom->removeRoom(this);
    parentRoom = nullptr;
    masterPointer = nullptr;
}

// ----------------------------------

void User::chooseRoom(Room* newRoom){
    if(this->parentRoom != nullptr){
		parentRoom->removeRoom(this);
	}
    newRoom->addRoom(this);
}

// ----------------------------------

void User::receiveMessage(Message inMessage){
    log.push_back(inMessage); //tbd
    thread->sendMessage(inMessage);
}

// ----------------------------------

void User::sendMessage(Message outMessage){
    parentRoom->receiveMessage(outMessage);
    log.push_back(outMessage);
}

// ----------------------------------

void User::initRoom(string name){
    parentRoom->addRoom(masterPointer->createRoom(name));
}

// ----------------------------------

void User::setThread(class Thread* inThread) {
    thread = inThread;
}

// ----------------------------------

void User::requestStruct() {
    thread->requestStruct();
}

// ----------------------------------

void User::setFilePath() {
    //dummy
}

// ----------------------------------

void User::readAllFromFile() {
    //Dummy to replace function from room.
}

// ----------------------------------

vector<string> User::getStruct() {
    return parentRoom->getStruct();
}
