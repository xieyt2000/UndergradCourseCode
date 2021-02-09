#include "weatherballoon.h"
#include "ui_weatherballoon.h"
weatherBalloon::weatherBalloon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::weatherBalloon)
{
    udpSocket.bind(5824);//绑定端口号
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(sendDatagram()));
    connect(&udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
    timer.start(2*1000);
    temperature = 10.2;
    humidity   = 5.4;
    altitude   = 100.0;
    setWindowTitle(tr("Weather Balloon"));
}
weatherBalloon::~weatherBalloon()
{
    delete ui;
}
void weatherBalloon::sendDatagram(){
    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    out<<QDateTime::currentDateTime()<<temperature<<humidity<<altitude;
    qDebug()<<QDateTime::currentDateTime();
    QHostAddress address;
    address.setAddress("192.168.0.46");//发送者要把数据发送到的ip地址
    udpSocket.writeDatagram(datagram,address,5824);//发送者把数据发送的端口号，需要接受者绑定该端口号
}
void weatherBalloon::processPendingDatagrams(){
    qDebug()<<"receive";
   QByteArray datagram;//拥于存放接收的数据报
   do{
       datagram.resize(udpSocket.pendingDatagramSize());//让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
       udpSocket.readDatagram(datagram.data(),datagram.size());//接收数据报，将其存放到datagram中
   }while(udpSocket.hasPendingDatagrams());//拥有等待的数据报
   QDateTime dateTime;
   double temperature;
   double humidity;
   double altitude;
   qDebug()<<"recive date ";
   QDataStream in(&datagram,QIODevice::ReadOnly);
   in.setVersion(QDataStream::Qt_4_3);
   in>>dateTime>>temperature>>humidity>>altitude;
   ui->dateLineEdit->setText(dateTime.date().toString());
   ui->timeLineEdit->setText(dateTime.time().toString());
   ui->temperatureLineEdit->setText(tr("%1 °c").arg(temperature));
   ui->humidityLineEdit->setText(tr("%1%").arg(humidity));
   ui->altiudeLineEdit->setText(tr("%1 m").arg(altitude));
}
