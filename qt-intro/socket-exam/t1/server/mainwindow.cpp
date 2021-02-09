#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTimer>
const int sizeOneTime=16*1024;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server=new QTcpServer(this);
    server->listen(QHostAddress::LocalHost, 8888);
    connect(server, &QTcpServer::newConnection, this, &MainWindow::newConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{
    socket=server->nextPendingConnection();
    QObject::connect(socket,&QTcpSocket::readyRead, this, &MainWindow::recvMessage);
}

void MainWindow::recvMessage()
{
    QString path;
    path= this->socket->readAll();
    if(path.length()==0)
    {
        qDebug()<<"fuck";
        return;
    }
    qDebug()<<path;
    QFile file(path);
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    if(!file.open(QFile::ReadOnly))
    {
        out<<qint64(0);
        socket->write(arr);
        return;
    }
     qDebug()<<"path";
    qint64 size = file.size();
    out<<size;
    QString name = path.split("\\").last();
    qDebug()<<name;
    socket->write(arr);
    socket->waitForBytesWritten(100);
    ui->textEdit->append(path); ui->textEdit->append(name);
    for (int cur = 0; cur < size;)
    {
        //qDebug()<<"start";
        QByteArray block=file.read(sizeOneTime); //4096
        cur += block.size();
        qDebug()<<block;
        socket->write(block);
        qDebug()<<cur;
        /*QEventLoop eventloop;
        QTimer::singleShot(1, &eventloop, SLOT(quit()));
        eventloop.exec();*/
    }
}
