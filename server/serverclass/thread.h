/*
FILNAMN: 		server.h
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#ifndef THREAD
#define THREAD

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <iostream>
#include <string>
#include "../master/master.h"

class User;

class Thread : public QThread {
    
    Q_OBJECT
public:
    Thread(qintptr ID, Master* masterptr, QObject *parent=nullptr);
    void run();
    void sendMessage(std::string);
    void reinitiate();
    
    
signals:
    void error(QTcpSocket::SocketError socketerror);
    
    
    
public slots:
    void readyRead();
    void disconnected();
    
private:
    QTcpSocket* TcpSocket;
    qintptr socketDescriptor;
    Master* masterPointer;
    User* userPointer;
};

#endif