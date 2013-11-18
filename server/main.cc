/*
FILNAMN: 		main.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#include "master/master.h"

int main() {
	Master master;
	master.createRoom("Room1");
	master.createRoom("Room2");
	std::cout << master.getRoom("Room1")->getName() << std::endl;
	std::cout << master.getRoom("Room2")->getName() << std::endl;
	
    return 0;
}
