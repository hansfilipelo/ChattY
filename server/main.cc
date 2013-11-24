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
   // cout << "1" << endl;
    master->createUser("David");
    
    //cout << "2 " << endl;
    //top->listUsers();
    Message testmess("Niklas tv är gay.", "David","Erik");
    //cout << "3" << endl;
    top->getRoom("David")->sendMessage(testmess);
    //cout << "4" << endl;
    
   // cout << top->getRoom("Erik")->getMessage(0).getMessage() << endl;
    
    master->createUser("Erik0");
    master->createUser("Erik1");
    master->createUser("Erik2");
    master->getRoom("Erik0")->chooseRoom(Room1);
    master->getRoom("Erik1")->chooseRoom(Room2);
   // top->listUsers();
    //top->listRooms();
    
    
    
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
	*/
    delete master;
    std::cout << "destroyed" << std::endl;
    return 0;
}
