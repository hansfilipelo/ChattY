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
    master->createUser("Erik");
    master->createUser("David");
    Message testmess("Niklas tv är gay.", "David","Erik");
    dynamic_cast<User*>(top->getRoom("David"))->sendMessage(testmess);
    std::cout<<dynamic_cast<User*>(top->getRoom("Erik"))->getMessage(0).getMessage()<<std::endl;
	
	//konstigt segfault på vektorn i getMessage i user och room
	
	
	
	/*
	top->createRoom("Room1");
	top->createRoom("Room2");
	std::cout << master->getRoom("Room1")->getName() << std::endl;
	std::cout << master->getRoom("Room2")->getName() << std::endl;
	std::cout << top->getRoom("Erik")->getName() << std::endl;

	
	User* Erik = dynamic_cast<User*>(top->getRoom("Erik"));
	Erik->chooseRoom(master->getRoom("Room2"));
	std::cout <<"omgang 2 " << master->getRoom("Room2")->getRoom("Erik")->getName()<< std::endl;
	std::cout << top->getRoom("Erik")->getName() << std::endl;
	
    delete master;
    std::cout << "destroyed" << std::endl;
    */
    std::cout<<"hej";
    return 0;
}
