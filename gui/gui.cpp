#include "gui.h"
#include "../client/NetClient.h"

Gui::Gui()
{
    Gui::Gui(){
        loginWindow = new LoginDialog();
        mainWindow = new ChatWindow();
        mainWindow->show();
        loginWindow->setModal(true);
        loginWindow->show();
    }
}

// --------------------------

void Gui::receiveMessage(QString from, QString to, QString message, QString servertime) {
    mainWindow->receiveMessage(from, to, message, servertime);
}
