/*
 FILNAMN: 		main.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-19
 BESKRIVNING:
 */

#include <iostream>
#include <stdio.h>
#include "netClient.h"
#include <QCoreApplication>


using namespace std;

int main(int argc,char *argv[])
{
    QCoreApplication a(argc,argv);
    
    string name;
    cout << "Skriv in ditt namn: ";
    cin >> name;
    
    string address;
    cout << "Skriv in serveraddress: ";
    
    cin.ignore(256,' ');
    for (std::string line; std::getline(std::cin, line);)
    {
        cout<<"vi kom in i for"<<endl;
        if (line.empty()){
            address="127.0.0.1";
            break;
        }
        else {
            address=line;
            cout<<address<<endl;
            break;
        }
    }
    
    NetClient client(name,address);
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
            client.sendMessage(input);
        }
    }
    
    
    return 0;
}