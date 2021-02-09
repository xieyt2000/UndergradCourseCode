#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QRect>
#include<QtDebug>
#include<QFileDialog>
#include<QTextStream>
#include<QInputDialog>
#include<QMessageBox>
#include<QNetworkInterface>
#include<QLCDNumber>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->centralWidget, &boardWidget::sendBoardMessage, this, &MainWindow::sendMeessage);
    connect(ui->centralWidget, &boardWidget::changeLCDTimer, ui->lcdNumber, [=](int val){
        ui->lcdNumber->display(val);
    });
}

MainWindow::~MainWindow()
{
    readWriteSocket->abort();
    delete ui;
}

void MainWindow::on_actionResign_triggered()
{
    ui->centralWidget->mySideResign();
}

void MainWindow::on_actionLoad_triggered()
{
    QFileDialog* fileDialog=new QFileDialog(this);
    QVector<QStringList> parsed;
    if(fileDialog->exec() == QDialog::Accepted) {
        QString path = fileDialog->selectedFiles()[0];
        QFile* file=new QFile(path);
        QString line;
        if(file->open(QFile::ReadOnly))
        {
            QTextStream in(file);
            while (1) {
                line=in.readLine();
                if(line.length()==0) break;
                QStringList tmpList=line.split(" ");
                parsed.append(tmpList);
            }
            ui->centralWidget->loadABoard(parsed);
            ui->centralWidget->genBoardStrAndSend();
            ui->centralWidget->startCountDown();
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFileDialog* fileDialog=new QFileDialog(this);
    QString path;
    if(fileDialog->exec() == QDialog::Accepted) {
        path = fileDialog->selectedFiles()[0];
    }
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        QStringList Lines=ui->centralWidget->generateCurBoard();
        for(auto line : Lines)
        {
            if(line.length()==0) break;
            textStream<<line<<endl;
        }
        file.close();
    }
}


void MainWindow::on_actionCreateServer_triggered()
{
    QInputDialog* IPDialog=new QInputDialog(this);
    IPDialog->setLabelText("Enter Server IP");
    IPDialog->setTextValue("127.0.0.1");
    for(auto i : QNetworkInterface::allAddresses())
    {
        qDebug()<<i.toString();
    }
    connect(IPDialog, &QInputDialog::textValueSelected, this, &MainWindow::createServer);
    IPDialog->show();
}

void MainWindow::on_actioncConnectServer_triggered()
{
    QInputDialog* IPDialog=new QInputDialog(this);
    IPDialog->setLabelText("Enter Server IP");
    IPDialog->setTextValue("127.0.0.1");
    connect(IPDialog, &QInputDialog::textValueSelected, this, &MainWindow::connectToServer);
    IPDialog->show();
}

void MainWindow::acceptConnection()
{
    this->readWriteSocket =this->listenSocket->nextPendingConnection();
    ui->centralWidget->mySide=whiteSide;
    QObject::connect(this->readWriteSocket,&QTcpSocket::readyRead,this,&MainWindow::recvMessage);
    ui->centralWidget->startCountDown();
}

void MainWindow::createServer(QString IP)
{
    if(!validIPstr(IP)) return;
    this->listenSocket =new QTcpServer(this);
    if(this->listenSocket->listen(QHostAddress(IP),8888)){
    }
    else {
        qDebug()<<listenSocket->errorString();
        QMessageBox::warning(this, "IP Issue", "Failed to create server");
        return;
    }
    waiting=new waitingDialog(this);
    waiting->show();
    connect(waiting, &waitingDialog::rejected, this->listenSocket, &QTcpServer::close);
    connect(this->listenSocket, &QTcpServer::newConnection, this, &MainWindow::acceptConnection);
    connect(this->listenSocket, &QTcpServer::newConnection, waiting, &waitingDialog::close);
}

void MainWindow::connectToServer(QString IP)
{
    if(!validIPstr(IP)) return;
    this->readWriteSocket = new QTcpSocket(this);
    this->readWriteSocket->connectToHost(QHostAddress(IP),8888);
    ui->centralWidget->mySide=blackSide;
    QTimer* connectTimer=new QTimer(this);
    connectTimer->setInterval(3000);
    connectTimer->start();
    connect(connectTimer, &QTimer::timeout, this ,[=](){
        if(readWriteSocket==nullptr)
        {
            QMessageBox::warning(this, "Connection Fial","Can't connect to "+IP);
            connectTimer->stop();
            return;
        }
        if(readWriteSocket->state() != QTcpSocket::ConnectedState)
        {
            QMessageBox::warning(this, "Connection Fial","Can't connect to "+IP);
            connectTimer->stop();
        }
    });
    QObject::connect(this->readWriteSocket,&QTcpSocket::readyRead,this,&MainWindow::recvMessage);
}

void MainWindow::recvMessage()
{
    QTextStream in;
    QString recMess= this->readWriteSocket->readAll();
    in.setString(&recMess, QIODevice::ReadOnly);
    QVector<QStringList> parsed;
    QString line;
    while (1) {
        line=in.readLine();
        if(line.length()==0) break;
        QStringList tmpList=line.split(" ");
        parsed.append(tmpList);
    }
    if(parsed.length()==0) return;
    ui->centralWidget->loadABoard(parsed);
}

void MainWindow::sendMeessage(QString str)
{
    QByteArray array;
    array.append(str);
    this->readWriteSocket->write(array.data());
}

bool MainWindow::validIPstr(const QString &str)
{
    QRegExp rx2("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    if (!rx2.exactMatch(str))
    {
        QMessageBox::critical(this, "IP Issue", "IP not valid!");
        return false;
    }
    return true;
}

void MainWindow::on_actionCastling_triggered()
{
    if(!ui->centralWidget->nowIsMySide()) return;
    castlingDialog* csDialog=new castlingDialog(this);
    connect(csDialog, &castlingDialog::chooseKingSide, ui->centralWidget, [=](){
        ui->centralWidget->castling(kingside);
    });
    connect(csDialog, &castlingDialog::chooseQueenSide, ui->centralWidget, [=](){
        ui->centralWidget->castling(queenside);
    });
    csDialog->show();
}
