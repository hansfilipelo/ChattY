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
#include <iostream>
#include <string>
#include "../master/master.h"
#include "../room/room.h"
#include "../message/message.h"

class Thread : public QThread {
    
    Q_OBJECT
public:
    Thread(qintptr ID, Master* masterptr, QObject *parent=nullptr);
    void run();
    
signals:
    void error(QTcpSocket::SocketError socketerror);
    
    
    
public slots:
    void readyRead();
    void disconnected();
//    void sendMessage(std::string);
    
private:
    QTcpSocket* TcpSocket;
    qintptr socketDescriptor;
    Master* masterPointer;
    User* userPointer;


};

#endif