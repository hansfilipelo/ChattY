/*
FILNAMN: 		netClient.h
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

class NetClient : public QObject
{
    Q_OBJECT
public:
    NetClient(std::string, QObject *parent = 0);
    void test();
    void test2();
    void sendMessage(std::string);   // ("Operand Kod" + "//" + "Argument1, 2, 3, 4 ... " + "EOF sträng" )
    
signals:
    
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *tcpSocket;
    QString name;
    
};




#endif