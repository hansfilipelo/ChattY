/*
 FILNAMN: 		main.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-19
 BESKRIVNING:
 */

#include <iostream>
#include <stdio.h>
#include "NetClientConsole.h"
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
    
    QString qAddress = QString::fromStdString(address);
    
    string name;
    cout << "Skriv in ditt namn: ";
    cin >> name;
    
    QString qName = QString::fromStdString(name);
    
    NetClient client(qName,qAddress);
    client.start();
    
    ReadThread readLoop(&client,qName);
    readLoop.start();
    
    return app.exec();
}