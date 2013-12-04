#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
class Gui;

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(Gui* guiPointer);
    void receiveMessage(const QString to, const QString from, const QString message, const QString time);
    ~ChatWindow();
    void setName(QString inName);
    Gui* chatGui;

private slots:
    void on_sendButton_clicked();

    void on_messageInput_returnPressed();

    void on_messageInput_textEdited(const QString &arg1);

    void on_actionBlack_triggered(bool checked);

    void on_actionDefault_triggered(bool checked);

private:
    QString receiver;
    Ui::ChatWindow *ui;
    QString name;
};

#endif // CHATWINDOW_H
