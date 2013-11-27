/*
 FILNAMN: 		main.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-19
 BESKRIVNING:
 */

#include <iostream>
#include "netClient.h"
#include <QCoreApplication>


using namespace std;

int main(int argc,char *argv[])
{
    QCoreApplication a(argc,argv);
    
    string name;
    while (name.size() == 0)
    {
        cout << "Skriv in ditt namn: ";
        cin >> name;
    }
    NetClient client(name);
    client.start();
    
    
    string input;
    
    cout<<name<<": ";
    //hanterar tyvärr inte hela meddelandet
    while(cin >> input)
    {
        if (input.substr(0,8)=="/username")
        {
            cout<<name;
        }
        else if(input.substr(0,5)=="/exit")
        {
            break;
        }
        else if(input !="")
        {
            cout<<input.substr(0,5);
            client.sendMessage(input);
            
        }
    }
        
    
    return 0;
}