/*
FILNAMN: 		NetClient.h
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-19
BESKRIVNING:	
*/


#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QDebug>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QString>
#include <iostream>

class Gui;

class NetClient : public QObject
{
    Q_OBJECT
public:
    NetClient(std::string, std::string, Gui*, QObject *parent = 0);
    void start();
    void sendMessage(QString from, QString to, QString message);
    void setName(QString);
    
signals:
    
public slots:
    void connected();
    void disconnected();
    void readyRead();

private:
    Gui* guiPointer;
    QTcpSocket *TcpSocket;
    QString name;
    QString address;
    
};




#endif