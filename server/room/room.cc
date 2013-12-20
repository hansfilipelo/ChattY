/*
 FILNAMN: 		room.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-14
 BESKRIVNING:
 */

#include "room.h"
#include <QDir>
#include <QString>
#include <QDebug>


using namespace std;

// ----------------------------------
// Constructor
Room::Room(string inName,Master* master, Master* scrap){
    masterPointer = master;
    name = inName;
}

Room::Room(string inName,Master* master) {
    masterPointer = master;
    name = inName;
    this->setFilePath();
    this->readAllFromFile();
}

// ----------------------------------------
// Help functions

void ifRoomRemove(Room* inRoom) {
    User* userTemp = dynamic_cast<User*>(inRoom);
    
    if (userTemp == nullptr) {
        inRoom->masterPointer->removeRoom(inRoom->getName());
    }
}

// ----------------------------------------
// Destructor

// Used on destruction to throw users up one step in the hierarchy
void throwUp(Room* inRoom) {
    inRoom->chooseRoom(inRoom->parentRoom->parentRoom);
}

Room::~Room() {
    for_each(rooms.begin(), rooms.end(), ifRoomRemove);
    
    if ( parentRoom == nullptr) {
        rooms.clear();
    }
    else {
        
        parentRoom->removeRoom(this);
        
        for_each(rooms.begin(), rooms.end(), throwUp);
        parentRoom = nullptr;
    }
    
    masterPointer = nullptr;
    
}

// ----------------------------------------

unsigned int Room::getPosOfRoom(string name) const{
    for( unsigned int i = 0 ; i < rooms.size() ; i++) {
        if(rooms.at(i)->getName() == name){
            return i;
        }
    }
    throw logic_error("No such room in Rooms");
    return 0;
}

// ----------------------------------------
// Automatically called from child when child room is destroyed
void Room::removeRoom(Room* inRoom) {
    unsigned int pos = getPosOfRoom(inRoom->getName());
    rooms.at(pos) = nullptr;
    rooms.erase(rooms.begin() + pos);
}

// ----------------------------------

void Room::sendMessage(Message inMessage) {
    string to = inMessage.getTo();
    string from = inMessage.getFrom();
    
    if (inMessage.getTo() == inMessage.getFrom()) {
        string temp = "Stop whispering in your own ear. Don't you have any friends to talk to?";
        Message errorMessage(temp,name,from);
        getRoom(from)->receiveMessage(errorMessage);
    }
    else {
        try {
            getRoom(to)->receiveMessage(inMessage);
            getRoom(from)->receiveMessage(inMessage);
        } catch (...) {
            string temp = "No user named ";
            temp += to;
            temp += " in this room!";
            Message errorMessage(temp,name,from);
            getRoom(from)->receiveMessage(errorMessage);
        }
    }
}


// ----------------------------------

void Room::listRooms(){
    for (unsigned int it = 0; it < rooms.size() ; it++){
        User* userTemp = dynamic_cast<User*>(rooms.at(it));
        if(userTemp == nullptr ){
            cout << rooms.at(it)->getName() << endl;
        }
    }
    return;
}

// ----------------------------------

void Room::listUsers(){
    for (unsigned int it = 0; it < rooms.size() ; it++){
        User* userTemp = dynamic_cast<User*>(rooms.at(it));
        if( userTemp == nullptr ){
            continue;
        }
        else{
            cout << rooms.at(it)->getName() << endl;
        }
    }
    return;
}


// ----------------------------------

void Room::receiveMessage(Message inMessage) {
    string to = inMessage.getTo();
    
    // If to room, send to all and save to log
    if(to == name){
        log.push_back(inMessage);
        
        sendMessageAll(inMessage);
        saveToFile(inMessage);
    }
    
    // Else it's a whisper
    else{
        sendMessage(inMessage);
    }
}

// ----------------------------------

void Room::sendMessageAll(Message inMessage) {
    
    for (unsigned int i = 0; i < rooms.size(); i++) {
        User* userTemp = dynamic_cast<User*>(rooms.at(i));
        if ( userTemp == nullptr ) {
            continue;
        }
        rooms.at(i)->receiveMessage(inMessage);
    }
}

// ----------------------------------
// Add new subroom

void Room::addRoom(Room* inRoom) {
    this->rooms.push_back(inRoom);
    inRoom->parentRoom = this;
}


// ----------------------------------
// Saves message to file

void Room::saveToFile(Message inMessage) {
    setFilePath();
    
    ofstream logfile;
    logfile.open (filepath, std::ios_base::app);
    
    logfile << inMessage.getServerTime() << endl << inMessage.getFrom() << endl;
    logfile << inMessage.getTo() << endl << inMessage.getMessage() << endl;
    
    logfile.close();
}
//-----------------------------------
// Sets file path for where to save current logs

void Room::setFilePath() {
    
    QDir dir = QDir::homePath();
    QString qAbsolutePath;
    string absolutePath;
    qAbsolutePath = dir.absolutePath();
    absolutePath = qAbsolutePath.toStdString();
    string today;
    today = absolutePath + "/ChattYlogs/" + name + currentDateTime().substr(0,10) + ".txt";
    
    if(not(filepath.empty()) && filepath != today )
    {
        log.clear();
        date = today;
    }
    
    if (!dir.cd("ChattYlogs")) {
        dir.mkpath("ChattYlogs");
        filepath = absolutePath + "/ChattYlogs/" + name + currentDateTime().substr(0,10) + ".txt";
    }
    else{
        dir.cd("ChattYlogs"); // for new rooms;
        filepath = absolutePath + "/ChattYlogs/" + name + currentDateTime().substr(0,10) + ".txt";
    }
    
    
}

// -----------------------------------
// Reads todays chat logs on startup

void Room::readAllFromFile() {
    log.clear();
    string line;
    ifstream logfile (filepath);
    
    if (logfile.is_open())
    {
        while (getline(logfile,line)) {
            string time = line;
            
            getline (logfile,line);
            string from = line;
            
            getline (logfile,line);
            string to = line;
            
            getline (logfile,line);
            string message = line;
            
            
            Message tempMessage(message,from,to,time);
            log.push_back(tempMessage);
        }
        logfile.close();
    }
    else {
        cout << "fel vid inläsning" << endl;
    }
}

// ------------------------------------

string Room::getName() {
    return name;
}

// ------------------------------------

void Room::createRoom(std::string inName){
	addRoom(masterPointer->createRoom(inName));
}

// ------------------------------------

Room* Room::getRoom(std::string name){
    for( unsigned int i = 0 ; i < rooms.size() ; i++) {
        if(rooms.at(i)->getName() == name){
            return rooms.at(i);
        }
    }
    throw logic_error("No such room in Rooms");
    
    return nullptr;
}

// -----------------------------------

Message Room::getMessage(unsigned int i){
    if (log.size() < i){
        throw logic_error{"No message at that position!"};
    }
    return log.at(i);
}

// -----------------------------------
// This function is only used on subclass User.

void Room::chooseRoom(Room*) {
    throw logic_error{"You're a retard since you're trying to move a room."};
}

// -----------------------------------

Room* Room::getParentRoom() {
    return parentRoom;
}

// -----------------------------------
/* 
 Creates a vector containing the contents of the room in form of strings for listing in the client. 
 The vector is built like this:
 
    <room1, room2, ..., roomN, User, user1, user2, ..., userN>

*/

vector<string> Room::getStruct() {
    vector<string> structure;
    
    if ( parentRoom != nullptr ) {
        structure.push_back(parentRoom->getName());
    }
    
    structure.push_back(name);
    structure.push_back("User");
    
    
    for (unsigned int i = 0; i < rooms.size() ; i++) {
        User* userTemp = dynamic_cast<User*>(rooms.at(i));
        if ( userTemp == nullptr ) {
            structure.insert(structure.begin(),rooms.at(i)->getName());
        }
        else {
            structure.push_back(rooms.at(i)->getName());
        }
    }
    
    return structure;
}


// -------------------------------------
// This function is only used on subclass User.

void Room::requestStruct() {
    throw logic_error{"You're a retard since you're trying to do stuff to a room. You naughty naughty boy."};
}


// -----------------------------------
/*
 Reads from old log files if requested by client. Takes in-arg telling how many days back requested log file is.
 */

vector<Message> Room::readOldFromFile(unsigned int dayCounter) {
    vector<Message> returnLog;
    string line;
    
    int i = 0 - dayCounter;
    
    // Clear in case of earlier read
    string oldFilePath = "";
    
    // Gets old date.
    QDate oldDate;
    oldDate = QDate::currentDate();
    oldDate = oldDate.addDays(i);
    
    QString oldDateString = oldDate.toString("yyyy-MM-dd");
    
    // Get path and cd to home folder
    QDir dir = QDir::homePath();
    dir.cd("ChattYlogs");
    QString qAbsolutePath = dir.absolutePath();
    string absolutePath = qAbsolutePath.toStdString();
    
    oldFilePath += absolutePath + "/" + name + oldDateString.toStdString() + ".txt";
    
    ifstream logfile (oldFilePath);
    
    // Read file.
    if (logfile.is_open())
    {
        while (getline(logfile,line)) {
            string time = line;
            
            getline (logfile,line);
            string from = line;
            
            getline (logfile,line);
            string to = line;
            
            getline (logfile,line);
            string message = line;
            
            Message tempMessage(message, from, to, time);
            returnLog.push_back(tempMessage);
        }
        
        logfile.close();
        return returnLog;
    }
    // Send info to client if there's no log file for given date. 
    else {
        string tempString;
        tempString += "No chatlogs for date " + oldDateString.toStdString() + " in this room.";
        
        Message tempMessage(tempString, name, name);
        returnLog.push_back(tempMessage);
        
        return returnLog;
    }
}





