#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QUrl>
#include <QMediaPlayer>

void MainWindow::setImgAndPlaySound(foodType request)
{
    QMediaPlayer* player = new QMediaPlayer(this);
    curFood=request;
    switch (request) {
    case biscuit:
    {
        QPixmap pic(":/picture/biscuit.jpg");
        ui->label->setPixmap(pic);
        player->setMedia(QUrl("qrc:/sound/biscuit.wav"));
        break;
    }
    case cola:
    {
        QPixmap pic(":/picture/cola.jpg");
        ui->label->setPixmap(pic);
        player->setMedia(QUrl("qrc:/sound/cola.wav"));
        break;
    }
    case noodle:
    {
        QPixmap pic(":/picture/noodle.jpg");
        ui->label->setPixmap(pic);
        player->setMedia(QUrl("qrc:/sound/noodle.wav"));
        break;
    }
    case steak:
    {
        QPixmap pic(":/picture/steak.jpg");
        player->setMedia(QUrl("qrc:/sound/steak.wav"));
        ui->label->setPixmap(pic);
        break;
    }
    }
    player->setVolume(100);
    player->play();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setImgAndPlaySound(biscuit);
    timer=new QTimer;
    timer->setInterval(2000);
    connect(timer, &QTimer::timeout, this, &MainWindow::timeoutUpdate);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    setImgAndPlaySound(biscuit);
    timer->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    setImgAndPlaySound(steak);
    timer->start();
}

void MainWindow::on_pushButton_3_clicked()
{
    setImgAndPlaySound(noodle);
    timer->start();
}

void MainWindow::on_pushButton_4_clicked()
{
    setImgAndPlaySound(cola);
    timer->start();
}

void MainWindow::timeoutUpdate()
{
    switch (curFood) {
    case biscuit:
    {
         curFood=steak;
         break;
    }
    case steak:
    {
        curFood=noodle;
        break;
    }
    case noodle:
    {
        curFood=cola;
        break;
    }
    case cola:
    {
        curFood=biscuit;
        break;
    }
    }
    setImgAndPlaySound(curFood);
    timer->start();
}
