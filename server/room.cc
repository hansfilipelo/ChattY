/*
FILNAMN: 		room.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:			2013-11-14
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

void Room::sendMessage(message* inMessage) {
    string to = inMessage.to;
    
    if ( not(log.find(to)) ) {
        message* errorMessage = new message("User does not exist", name, inMessage.from, time(0));
        
    }
    
}