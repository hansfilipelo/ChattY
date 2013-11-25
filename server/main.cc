/*
FILNAMN: 		main.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#include "master/master.h"
#include <iostream>

using namespace std;

int main() {
	Master* master = new Master();
    Room* top = master->getTop();
	
    Room* Room1 = master->createRoom("Room1");
    Room* Room2 = master->createRoom("Room2");
    
    top->addRoom(Room1);
	Room1->addRoom(Room2);
    
    master->createUser("Erik");
    master->createUser("David");
    
    Message testmess("Niklas tv är gay.", "David","Erik");
    top->getRoom("David")->sendMessage(testmess);
    
    master->createUser("Erik0");
    master->createUser("Erik1");
    master->createUser("Erik2");
    master->getRoom("Erik0")->chooseRoom(Room1);
    master->getRoom("Erik1")->chooseRoom(Room2);
    
    
    
    cout << "listing users in top" << endl;
    top->listUsers();
    cout << "listing users in Room1" << endl;
    Room1->listUsers();
    cout << "listing users in Room2" << endl;
	Room2->listUsers();
 
    cout << "Destroying Room1" << endl;
    master->removeRoom("Room1");
    cout << "should see Erik0, Erik1, Erik, Erik2, David" << endl;
    top->listUsers();

    delete master;
    std::cout << "destroyed" << std::endl;
    return 0;
}
