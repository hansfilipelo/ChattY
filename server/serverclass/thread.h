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
#include "../message/message.h"
#include "../master/master.h"
#include "../room/room.h"

class User;

class Thread : public QThread {
    
    Q_OBJECT
public:
    Thread(qintptr ID, Master* masterptr, QObject *parent=nullptr);
    void run();
    void sendMessage(Message);
    void reinitiate();
    void sendVector();
    void sendHistory();
    void requestStruct();
    
signals:
    void error(QTcpSocket::SocketError socketerror);
    
    
    
public slots:
    void readyRead();
    void disconnected();
    
protected:
    void handleMessage(QString);
    void handleInitiate(std::string);
    void handleStructure();
    
private:
    QTcpSocket* TcpSocket;
    qintptr socketDescriptor;
    Master* masterPointer;
    User* userPointer;
    QByteArray compare;
    QByteArray breaker;
};

#endif