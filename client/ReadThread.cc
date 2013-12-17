/*
FILNAMN: 		readThread.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-28
BESKRIVNING:	
*/

#include "ReadThread.h"

using namespace std;


ReadThread::ReadThread(NetClient* inClient){
    client = inClient;
}

void ReadThread::run() {
    
    string input;
    
    //hanterar tyvärr inte hela meddelandet
    while(cin >> input)
    {
        if (input.substr(0,8)=="/username")
        {
            break;
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