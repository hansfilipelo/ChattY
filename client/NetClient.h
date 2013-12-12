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
#include <stdexcept>
#include <QHostInfo>

class Gui;

class NetClient : public QObject
{
    Q_OBJECT
public:
    NetClient(QString, QString, Gui*, QObject *parent = 0);
    void start();
    void sendMessage(QString, QString, QString);
    void setName(QString);
    void getStruct();
    
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
    QByteArray compare;
    QByteArray breaker;
    void handleHistory(QString);
    void handleMessage(QString);
    void handleStructure(QString);
};




#endif
