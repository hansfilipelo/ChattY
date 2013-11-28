/*
FILNAMN: 		readThread.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-28
BESKRIVNING:	
*/

#include "ReadThread.h"

using namespace std;


ReadThread::ReadThread(NetClient* inClient, string inName){
    client = inClient;
    name = inName;
}

void ReadThread::run() {
    
    string input;
    
    //hanterar tyvärr inte hela meddelandet
    while(cin >> input)
    {
        cout << name << ": ";
        if (input.substr(0,8)=="/username")
        {
            cout << name;
        }
        else if(input.substr(0,5)=="/exit")
        {
            break;
        }
        else if(input !="")
        {
            client->sendMessage(input);
        }
    }
    
}