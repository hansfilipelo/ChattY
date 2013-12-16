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
    QString tempString = time;
    ui->messageHistory->moveCursor(QTextCursor::End);
    ui->messageHistory->setTextColor(Qt::black);
    ui->messageHistory->insertPlainText(tempString.remove(0,11).remove(5,7)+" | ");

    if(to == name){
        lastWhisper=from;
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

    //här har jag pillat
    ui->messageHistory->insertHtml(smilieConvert(message));


    //ui->messageHistory->insertHtml( "<img src=':/files/smilies/images/ledsen.png' width='15' height='15'>");
    ui->messageHistory->insertPlainText("\n");
    ui->messageHistory->moveCursor(QTextCursor::End);
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
    ui->roomTree->clear();
    QTreeWidgetItem *treeParent;
    treeParent=addRoot(treeStruct.at(0));
    for (int i=1; i< treeStruct.size(); i++){
        if (treeStruct.at(i)=="User"){
            treeStruct.remove(i);
            while (i < treeStruct.size()){
                addLeaf(treeParent,treeStruct.at(i));
                i++;
            }
        }
        else {
            treeParent=addSubRoot(treeParent,treeStruct.at(i));
        }
    }
    ui->roomTree->expandAll();
}

QTreeWidgetItem* ChatWindow::addRoot(const QString rootName){
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->roomTree);
    item->setText(0,rootName);
    ui->roomTree->addTopLevelItem(item);
    return item;

}

QTreeWidgetItem* ChatWindow::addSubRoot(QTreeWidgetItem *parent,const QString subRootName){
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,subRootName);
    parent->addChild(item);
    return item;
}

void ChatWindow::addLeaf(QTreeWidgetItem *parent,const QString leafName){
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,leafName);
    parent->addChild(item);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}


//If sendbutton is pressed display sent from text and message in messagehistory//
void ChatWindow::on_sendButton_clicked()
{
    sendMessage();
    ui->messageInput->clear();
    receiver="root";
    ui->sendButton->setText("Send");

}

// send message on return//
void ChatWindow::on_messageInput_returnPressed()
{
    on_sendButton_clicked();

}


//Slash command control//
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
    if(w=="/r " or w=="/R "){
        to.remove("/r ",Qt::CaseInsensitive);
        receiver=lastWhisper;
        ui->sendButton->setText("To " + receiver);
        ui->messageInput->clear();

    }
}

void ChatWindow::sendMessage(){
    if (ui->messageInput->text()==""){
        return;
    }
    else{
        chatGui->sendMessage(name,receiver,ui->messageInput->text());
    }

}


void ChatWindow::receiveHistory(QVector<QString> &historyVector){
    for(int i = 0;i<historyVector.size(); i+=4){
        QString tempString=historyVector.at(i+3);
        ui->messageHistory->setTextColor(Qt::black);
        ui->messageHistory->insertPlainText(tempString.remove(0,11).remove(5,7)+" | ");
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText(historyVector.at(i) + " says: ");
        ui->messageHistory->setTextColor(Qt::black);
        ui->messageHistory->insertHtml(smilieConvert(historyVector.at(i+2)));
        ui->messageHistory->insertPlainText("\n");
        ui->messageHistory->moveCursor(QTextCursor::End);

    }
}

void ChatWindow::receiveOldHistory(QVector<QString> &historyVector){
    ui->messageHistory->moveCursor(QTextCursor::Start);
    for(int i = 0;i<historyVector.size(); i+=4){
        QString tempString=historyVector.at(i+3);
        ui->messageHistory->setTextColor(Qt::black);
        ui->messageHistory->insertPlainText(tempString.remove(0,11).remove(5,7)+" | ");
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText(historyVector.at(i) + " says: ");
        ui->messageHistory->setTextColor(Qt::black);
        ui->messageHistory->insertHtml(smilieConvert(historyVector.at(i+2)));
        ui->messageHistory->insertPlainText("\n");

    }
    ui->messageHistory->moveCursor(QTextCursor::End);
}

void ChatWindow::getHistory(){
    //chatGui->getHistory();
}

void ChatWindow::clearHistory(){
    ui->messageHistory->clear();
}


//---------------------------------Customisation menu-------------------------------//



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


void ChatWindow::on_actionChatty_triggered()
{
    setStyleSheet("ChatWindow{border-image:url(:/files/icon/ChattY.png) 0 0 0 0 stretch stretch;}");
    ui->menuBar->setStyleSheet("background-color: transparent;");
    ui->statusBar->setStyleSheet("background-color: transparent;");
    ui->centralWidget->setStyleSheet("background-color: transparent;");
    ui->sendButton->setStyleSheet("background-color: none;");
}

void ChatWindow::on_actionCezch_triggered()
{
    setStyleSheet("ChatWindow{background-color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(255, 255, 255, 255), stop:0.373979 rgba(255, 255, 255, 255), stop:0.373991 rgba(33, 30, 255, 255), stop:0.624018 rgba(33, 30, 255, 255), stop:0.624043 rgba(255, 0, 0, 255), stop:1 rgba(255, 0, 0, 255));}");
    ui->menuBar->setStyleSheet("background-color: transparent;");
    ui->statusBar->setStyleSheet("background-color: transparent;");
    ui->centralWidget->setStyleSheet("background-color: transparent;");
    ui->sendButton->setStyleSheet("background-color: none;");
}

void ChatWindow::on_roomTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    receiver = item->text(column);
    ui->sendButton->setText("To " + receiver);
    ui->messageInput->setFocus();
    ui->messageInput->setCursorPosition(0);
}

QString ChatWindow::smilieConvert(const QString inMessage){
    QString messageConv = inMessage.toHtmlEscaped();
    messageConv.replace(":)",happyFace);
    messageConv.replace(":(",sadFace);
    messageConv.replace(":|",straightFace);
    messageConv.replace(":o",oFace);
    messageConv.replace("xD",xdFace);
    return messageConv;
}

//-------------Change font menu----------------------------------------------//

void ChatWindow::on_action13_triggered()
{
    QFont f("Geeza Pro", 13);
    ui->messageHistory->setFont(f);
    ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
}

void ChatWindow::on_action15_triggered()
{
    QFont f("Geeza Pro", 15);
    ui->messageHistory->setFont(f);
    ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
}

void ChatWindow::on_action20_triggered()
{
    QFont f("Geeza Pro", 20);
    ui->messageHistory->setFont(f);
    ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
}

void ChatWindow::on_action25_triggered()
{
    QFont f("Geeza Pro", 25);
    ui->messageHistory->setFont(f);
    ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
}



//--------------------------------Smiley size menu--------------------------------------//


void ChatWindow::on_action13_2_triggered()
{
     happyFace = "<img src=':files/smilies/happyface.png' width='13' height='13'>";
     sadFace = "<img src=':files/smilies/sadface.png' width='13' height='13'>";
     straightFace = "<img src=':files/smilies/straightface.png' width='13' height='13'>";
     oFace = "<img src=':files/smilies/oface.png' width='13' height='13'>";
}

void ChatWindow::on_action15_2_triggered()
{
    happyFace = "<img src=':files/smilies/happyface.png' width='15' height='15'>";
    sadFace = "<img src=':files/smilies/sadface.png' width='15' height='15'>";
    straightFace = "<img src=':files/smilies/straightface.png' width='15' height='15'>";
    oFace = "<img src=':files/smilies/oface.png' width='15' height='15'>";
}

void ChatWindow::on_action20_2_triggered()
{
    happyFace = "<img src=':files/smilies/happyface.png' width='20' height='20'>";
    sadFace = "<img src=':files/smilies/sadface.png' width='20' height='20'>";
    straightFace = "<img src=':files/smilies/straightface.png' width='20' height='20'>";
    oFace = "<img src=':files/smilies/oface.png' width='20' height='20'>";
}

void ChatWindow::on_action25_2_triggered()
{
    happyFace = "<img src=':files/smilies/happyface.png' width='25' height='25'>";
    sadFace = "<img src=':files/smilies/sadface.png' width='25' height='25'>";
    straightFace = "<img src=':files/smilies/straightface.png' width='25' height='25'>";
    oFace = "<img src=':files/smilies/oface.png' width='25' height='25'>";
}

void ChatWindow::on_actionNiklas_triggered()
{
    happyFace = "<img src=':files/smilies/happyface.png' width='120' height='120'>";
    sadFace = "<img src=':files/smilies/sadface.png' width='120' height='120'>";
    straightFace = "<img src=':files/smilies/straightface.png' width='120' height='120'>";
    oFace = "<img src=':files/smilies/oface.png' width='120' height='120'>";
}



//------------------History menu--------------------------------------------//

void ChatWindow::on_actionLoad_history_triggered()
{
    getHistory();
}
