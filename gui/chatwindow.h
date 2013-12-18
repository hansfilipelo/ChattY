#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QScrollBar>
#include <QTreeWidget>
#include <initializer_list>
#include <QGraphicsOpacityEffect>
#include <QDate>

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
    void receiveOldHistory(QVector<QString> &historyVector);
    void getHistory();
    void clearHistory();
    void setSmileySize(int);

private slots:
    void on_sendButton_clicked();

    void on_messageInput_returnPressed();

    void on_messageInput_textEdited(const QString &arg1);

    void on_actionBlack_triggered();

    void on_actionDefault_triggered();

    void on_actionChatty_triggered();

    void on_actionCezch_triggered();

    void on_roomTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_action13_triggered();

    void on_action15_triggered();

    void on_action20_triggered();

    void on_action25_triggered();

    void on_actionLoad_history_triggered();

    void on_action13_2_triggered();

    void on_action15_2_triggered();

    void on_action20_2_triggered();

    void on_action25_2_triggered();

    void on_actionNiklas_triggered();

    void on_actionNikki_Beach_triggered();

    void on_actionShe_squats_bro_triggered();

private:
    QString receiver="root";
    Ui::ChatWindow *ui;
    QString name;
    QString server;
    QString lastWhisper;
    QString smilieConvert(const QString);
    QString happyFace = "<img src=':/files/smilies/happyface.png' width='25' height='25'>";
    QString sadFace =  "<img src=':/files/smilies/sadface.png' width='25' height='25'>";
    QString straightFace = "<img src=':/files/smilies/straightface.png' width='25' height='25'>";
    QString xdFace = "<img src=':/files/smilies/xdface.png' width='25' height='25'>";
    QString oFace = "<img src=':/files/smilies/oface.png' width='25' height='25'>";
    QString astronaut= "<img src=':/files/smilies/astronaut.png' width='25' height='25'>";
    QString batman = "<img src=':/files/smilies/batman.png' width='25' height='25'>";
    QString grandpa = "<img src=':/files/smilies/grandpa.png' width='25' height='25'>";
    QString ironman = "<img src=':/files/smilies/ironman.png' width='25' height='25'>";
    QString spiderman = "<img src=':/files/smilies/spiderman.png' width='25' height='25'>";
    QString pirate = "<img src=':/files/smilies/pirate.png' width='25' height='25'>";
    QString angry = "<img src=':/files/smilies/angry.png' width='25' height='25'>";
    QString laurel= "<img src=':/files/smilies/laurel.png' width='25' height='25'>";
    QString smileySize;
    QVector<QString> smiley;
};

#endif // CHATWINDOW_H
