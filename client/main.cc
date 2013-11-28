/*
 FILNAMN: 		main.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-19
 BESKRIVNING:
 */

#include <iostream>
#include <stdio.h>
#include "NetClient.h"
#include <QCoreApplication>
#include <QEventLoop>
#include "ReadThread.h"


using namespace std;

int main(int argc,char *argv[])
{
    QCoreApplication app(argc,argv);
    
    cout << "Skriv in serveraddress: ";
    
    std::string address;
    std::getline(std::cin,address);
    if (address.empty() ){
        address = "127.0.0.1";
    }
    
    string name;
    cout << "Skriv in ditt namn: ";
    cin >> name;
    
    NetClient client(name,address);
    client.start();
    
    ReadThread readLoop(&client);
    readLoop.start();
    
    return app.exec();
}