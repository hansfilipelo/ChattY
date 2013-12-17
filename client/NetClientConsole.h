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
#include <QHostInfo>

class NetClient : public QObject
{
    Q_OBJECT
public:
    NetClient(QString, QString, QObject *parent = 0);
    void start();
    void sendMessage(std::string);
    void sendMessage(QString, QString, QString);
    
signals:
    
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void getHistory(unsigned int);

private:
    void handleHistory(QString);
    void handleMessage(QString);
    void handleStructure(QString);
    void handleRequestStruct();
    void handleOldHistory(QString);
    
    QTcpSocket *TcpSocket;
    QString name;
    QString address;
    
    QByteArray compare;
    QByteArray breaker;
};




#endif