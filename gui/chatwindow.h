#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QScrollBar>
#include <QTreeWidget>
#include <QDebug>
#include "smilies/smiley.h"

class Gui;

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(Gui* guiPointer);
    void receiveMessage(const QString from, const QString to, const QString message,const QString time);
    ~ChatWindow();
    void setName(QString inName);
    void setServer(QString serverName);
    void updateStruct(QVector<QString> treeStruct);
    QTreeWidgetItem *addRoot(const QString rootName);
    QTreeWidgetItem *addSubRoot(QTreeWidgetItem *parent,const QString childName);
    void addLeaf(QTreeWidgetItem *parent,const QString leafName);
    Gui* chatGui;
    void sendMessage();
    std::ofstream debug;
    void receiveHistory(QVector<QString> &historyVector);



private slots:
    void on_sendButton_clicked();

    void on_messageInput_returnPressed();

    void on_messageInput_textEdited(const QString &arg1);

    void on_actionBlack_triggered();

    void on_actionDefault_triggered();

    void on_actionChatty_triggered();

    void on_actionCezch_triggered();

    void on_roomTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    QString receiver="root";
    Ui::ChatWindow *ui;
    QString name;
    QString server;
    QString lastWhisper;
};

#endif // CHATWINDOW_H
