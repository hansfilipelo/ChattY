#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "QString"
#include "QColor"
#include "gui.h"
//

ChatWindow::ChatWindow(Gui* guiPointer) :
    QMainWindow(nullptr),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    chatGui = guiPointer;
}

void ChatWindow::receiveMessage(const QString from, const QString to, const QString message, const QString time){
    ui->messageHistory->moveCursor(QTextCursor::End);
    if(to == name){
        ui->messageHistory->setTextColor(Qt::magenta);
        ui->messageHistory->insertPlainText(from +" whispers to you: ");
        ui->messageHistory->setTextColor(Qt::black);

    }
    else if (from == name && to != "root"){
        ui->messageHistory->setTextColor(Qt::magenta);
        ui->messageHistory->insertPlainText("You whisper to " + to + ": ");
        ui->messageHistory->setTextColor(Qt::black);
    }

    else if (from == name && to == "root"){
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText("You say: ");
        ui->messageHistory->setTextColor(Qt::black);

    }
    else {
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText(from + " says: ");
        ui->messageHistory->setTextColor(Qt::black);
    }
    ui->messageHistory->insertPlainText(message);
    ui->messageHistory->insertPlainText("\n");
    if(ui->messageHistory->verticalScrollBar()->value() != ui->messageHistory->verticalScrollBar()->maximum())
    {

    }
    else{
        ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
    }

}

void ChatWindow::setName(QString inName){
    name = inName;
}

void ChatWindow::setServer(QString serverName){
     server = serverName;
     ui->roomTree->setHeaderLabel(server);
}

void ChatWindow::updateStruct(QVector<QString> treeStruct){
    QTreeWidgetItem* treeParent=new QTreeWidgetItem(ui->roomTree);
    treeParent=addRoot(treeStruct.at(0));
    for (int i=1; i<= treeStruct.size(); i++){
        if (treeStruct.at(i)=="User"){
            while (i+1 <= treeStruct.size()){
                addLeaf(treeParent,treeStruct.at(i+1));
                i++;
            }
        }
        treeParent=addSubRoot(treeParent,treeStruct.at(i));
    }
}

QTreeWidgetItem* ChatWindow::addRoot(const QString rootName){
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->roomTree);
    item->setText(0,rootName);
    ui->roomTree->addTopLevelItem(item);
    return item;

}

QTreeWidgetItem* ChatWindow::addSubRoot(QTreeWidgetItem *parent,const QString childName){
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->roomTree);
    item->setText(0,childName);
    parent->addChild(item);
    return item;
}

void ChatWindow::addLeaf(QTreeWidgetItem *parent,const QString leafName){
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->roomTree);
    item->setText(0,leafName);
    parent->addChild(item);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}


//If sendbutton is pressed display sent from text and message in messagehistory
void ChatWindow::on_sendButton_clicked()
{
    sendMessage();
    ui->messageInput->clear();
    receiver="root";
    ui->sendButton->setText("Send");

//observera at root är en templösning
}

// send message on return
void ChatWindow::on_messageInput_returnPressed()
{
    on_sendButton_clicked();

}


//whisper control
void ChatWindow::on_messageInput_textEdited(const QString &arg1)
{
    QString to      = arg1;
    QString w       = arg1;
    QString whisper = arg1;
    w.truncate(3);
    whisper.truncate(9);

    if(w == "/w " or w =="/W "){

        to.remove("/w ",Qt::CaseInsensitive);
        if(to.length() > 0 && to.endsWith(" ")){
            to.chop(1);
            receiver = to;
            ui->sendButton->setText("To " + to);
            ui->messageInput->clear();
        }
    }
    if(whisper == "/whisper " or whisper =="/Whisper "){

        to.remove("/whisper ",Qt::CaseInsensitive);
        if(to.length() > 0 && to.endsWith(" ")){
            to.chop(1);
            receiver = to;
            ui->sendButton->setText("To " + to);
            ui->messageInput->clear();
        }
    }
  //  if(w=="/r " or w=="/R "){

}


void ChatWindow::sendMessage(){
    chatGui->sendMessage(name,receiver,ui->messageInput->text());

}


void ChatWindow::on_actionBlack_triggered()
{
    ui->messageInput->setStyleSheet("color: black;"
                                    "background-color: grey;"
                                    "selection-color: black;"
                                    "selection-background-color: white");
    ui->roomTree->setStyleSheet("color: black;"
                                "background-color: grey;"
                                "selection-color: black;"
                                "selection-background-color: white");
    ui->messageHistory->setStyleSheet("color: black;"
                             "background-color: grey;"
                             "selection-color: black;"
                             "selection-background-color: white");
    this->setStyleSheet("color: white;"
                             "background-color: black;"
                             "selection-color: black;"
                             "selection-background-color: white");
    ui->mainToolBar->setStyleSheet("color: white;"
                               "background-color: black;"
                               "selection-color: black;"
                               "selection-background-color: white");

}

void ChatWindow::on_actionDefault_triggered()
{
    ui->messageInput->setStyleSheet("");
    ui->roomTree->setStyleSheet("");
    ui->messageHistory->setStyleSheet("");
    this->setStyleSheet("");
    ui->mainToolBar->setStyleSheet("");
}

}

void ChatWindow::receiveHistory(QVector<QString> &historyVector){
    for(int i = 0;i==historyVector.size(); i+=4){
        ui->messageHistory->insertPlainText(historyVector.at(i) + " says: " + historyVector.at(i+2) + "\n");
    }

}
