/*
FILNAMN: 		User.h
LABORATION:		
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
DATUM:			2013-11-14
BESKRIVNING:	
*/

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <Room.h>


class User : public Room
{
public:
    User(std::string);
    ~User();
    std::string name;
    void sendMessage(Message);
    void recieveMessage(Message);
    void chooseRoom(Room*);
    
private:
    std::vector<Message> log;
    Room* parentRoom;
    
};