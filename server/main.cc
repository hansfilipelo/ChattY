/*
FILNAMN: 		main.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#include "master/master.h"
#include <iostream>

int main() {
	Master* master = new Master();
    Room* top = master->getTop();
	top->addRoom(master->createRoom("Room1"));
	top->addRoom(master->createRoom("Room2"));
	std::cout << master->getRoom("Room1")->getName() << std::endl;
	std::cout << master->getRoom("Room2")->getName() << std::endl;
	
    delete master;
    std::cout << "destroyed" << std::endl;
    return 0;
}
