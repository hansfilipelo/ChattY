#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QScrollBar>
class Gui;

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(Gui* guiPointer);
    void receiveMessage(const QString from, const QString to, const QString message, const QString time);
    ~ChatWindow();
    void setName(QString inName);
    void sendMessage();
    std::ofstream debug;
    void receiveHistory(QVector<QString> &historyVector);



private slots:
    void on_sendButton_clicked();

    void on_messageInput_returnPressed();

    void on_messageInput_textEdited(const QString &arg1);

    void on_actionBlack_triggered();

    void on_actionDefault_triggered();

private:
    QString receiver="root";
    Ui::ChatWindow *ui;
    QString name;
    Gui* chatGui;
};

#endif // CHATWINDOW_H
