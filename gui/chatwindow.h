#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    void messageReceived(const QString to, const QString from, const QString message, const QString time);
    ~ChatWindow();

private slots:
    void on_sendButton_clicked();

    void on_messageInput_returnPressed();

    void on_messageInput_textEdited(const QString &arg1);

private:
    QString receiver;
    Ui::ChatWindow *ui;
};

#endif // CHATWINDOW_H
