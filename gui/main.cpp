#include "chatwindow.h"
#include "logindialog.h"
#include <QApplication>
#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui g;


    return a.exec();
}
