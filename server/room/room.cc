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

Room::Room(string inName,Master* master) {
    masterPointer = master;
    name = inName;
}

// ----------------------------------------
// Destructor

bool containsRoom(map<string,Room*> rooms){
       for (auto it = rooms.cbegin(); it != rooms.cend() ; it++ ){
        User* userTemp = dynamic_cast<User*>(it->second);
        if(userTemp == nullptr ){
            return true;
        }
    }
    return false;
}

// ----------------------------------------
//              Destructor

Room::~Room() {
    cout << containsRoom(rooms) << endl;
    while(containsRoom(rooms)) {
        for (auto it = rooms.cbegin(); it != rooms.cend() ; ){
            User* userTemp = dynamic_cast<User*>(it->second);
            if(userTemp == nullptr ){
                cout << it->second->name << "was removed as room" << endl;
                removeRoom(it->second);
                rooms.erase(it++);
                break;
            }
            it++;
        }
    }
    if(parentRoom == nullptr){
        cout << "should not happen" << endl;
        for (auto it = rooms.cbegin(); it != rooms.cend() ; ){
            delete it
            rooms.erase(it++);
        }
        return;
    }
    for (auto it = rooms.cbegin(); it != rooms.cend() ; it++){
        parentRoom->addRoom(it->second);
        cout << "should happen twice" << it->first << endl;
    }
    return;
}

// ----------------------------------------

void Room::removeRoom(Room* inRoom) {
    if ( rooms.find(inRoom->name) == rooms.end() ) {
        throw logic_error{"Trying to remove room that's not in this parent room"};
    }
    else {
        cout << inRoom->name << "was passed on to master by "<< this->name << endl;
        masterPointer->removeRoom(inRoom->name);
        rooms.erase(inRoom->name);
        
    }
}

// ----------------------------------------


//void destructHelp(Room* inRoom){
//    inRoom->parentRoom->rooms.erase(inRoom->parentRoom->rooms.find(inRoom->getName()));
//    delete inRoom;
//}
//
//Room::~Room() {
//
//    if(parentRoom == nullptr){
//        for (auto it = rooms.cbegin(); it != rooms.cend() ; ){
//            cout << this->getName() << endl;
//            rooms.erase(it++);
//        }
//        cout << "slut" << endl;
//        return;
//    }
//
//    vector<Room*> temp;
//    for (auto i = rooms.begin(); i != rooms.end(); i++) { //This might not work.
//        User* userTemp = dynamic_cast<User*>(i->second);
//        if ( userTemp == nullptr ) {
//            temp.push_back(i->second);
//        }
//    }
//
//    for_each(temp.begin(),temp.end(),destructHelp);
//
//    for (auto i = rooms.begin(); i != rooms.end(); i++) { //This might not work.
//            parentRoom->addRoom(i->second);
//        }
//
//    masterPointer->removeRoomHelp(name);
//    parentRoom->removeRoom(this);
//}

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

void Room::listRooms(){
    for (auto it = rooms.cbegin(); it != rooms.cend() ; it++){
        User* userTemp = dynamic_cast<User*>(it->second);
        if(userTemp == nullptr ){
            cout << it->first << endl;
        }
    }
    return;
}

// ----------------------------------

void Room::listUsers(){
    for (auto it = rooms.cbegin(); it != rooms.cend() ; it++){
        User* userTemp = dynamic_cast<User*>(it->second);
        if(userTemp == nullptr ){
            continue;
        }
        else{
            cout << it->first << endl;
        }
    }
    return;
}

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

void Room::addRoom(Room* inRoom) {
    inRoom->parentRoom = this;
    rooms.insert(pair<string, Room*>(inRoom->name,inRoom));
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

