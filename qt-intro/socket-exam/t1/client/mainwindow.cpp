#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<string>
#include<QTimer>
#include<QMessageBox>
using std::string;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::textChange, this, &MainWindow::changeText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToHost()
{
    socket=new QTcpSocket;
    socket->connectToHost(QHostAddress::LocalHost, 8888);
    //sock
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(true);
    source=ui->lineEdit->displayText(); target=ui->lineEdit_2->displayText();
    qDebug()<<target;
    connectToHost();
    QEventLoop eventloop;
    QTimer::singleShot(100, &eventloop, SLOT(quit()));
    eventloop.exec();
    QByteArray arr=source.toUtf8();
    socket->write(arr);
    qDebug()<<arr;
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::getfile);
    /*QEventLoop eventloop1;
    QTimer::singleShot(100, &eventloop, SLOT(quit()));
    eventloop.exec();*/
}

void MainWindow::getfile()
{
    if(!readone) return;
    readone=false;
    QDataStream info(socket);
    qint64 cur=0,size= 0;
    qDebug()<<"there";
    qDebug()<<size;
    QString sizeMB;
    info >> size;
    if(size==0)
    {
        QMessageBox::warning(this, "no file", "no file");
        readone=true;
        ui->pushButton->setDisabled(false);
        return;
    }
    double mb=size/1024.0/1024.0;
    sizeMB.append(QString::number(mb));
    sizeMB.append("MB");
    QString name = source.split("\\").back();
    QFile file(target+"\\"+name);
    if(!file.open(QFile::WriteOnly))
    {
        qDebug()<<"not oppen";
        return;
    }

    qDebug()<<"here";
    qDebug()<<size;
    while (cur < size)
    {
        qDebug()<<cur;

        socket->waitForReadyRead(150);
        QByteArray arr = socket->readAll();
        if(cur>4489200) qDebug()<<arr;
        cur += arr.size();
        file.write(arr);
        QString text;
        text.append("已发送");
        text.append(QString::number(cur/1024));
        text.append("KB 总共");
        text.append(sizeMB);
        emit textChange(text);
    }
    ui->pushButton->setDisabled(false);
    file.close();
    readone=true;
}

void MainWindow::changeText(QString txt)
{
    ui->textEdit->setText(txt);
}
