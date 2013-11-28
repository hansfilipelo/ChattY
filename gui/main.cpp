#include "chatwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog l;
    ChatWindow w;
    w.show();
    l.setModal(true);
    l.show();




    return a.exec();
}
