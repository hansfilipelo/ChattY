/*
FILNAMN: 		server.h
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#ifndef SERVER
#define SERVER

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include "thread.h"


class Server : public QTcpServer {
    
    Q_OBJECT
public:
    Server(QObject *parent=nullptr);
    void startServer();

signals:
    
    
public slots:

protected:
    void incomingConnection(qintptr handle);
    
    
};

#endif