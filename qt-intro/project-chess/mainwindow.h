#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<boardwidget.h>
#include<QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include<QString>
#include"waitingdialog.h"
#include"castlingdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionResign_triggered();

    void on_actionLoad_triggered();

    void on_actionSave_triggered();



    void on_actionCreateServer_triggered();

    void on_actioncConnectServer_triggered();

    void acceptConnection();

    void createServer(QString IP);

    void connectToServer(QString IP);

    void recvMessage();

    void sendMeessage(QString str);

    void on_actionCastling_triggered();

private:
    Ui::MainWindow *ui;
    QTcpServer  *listenSocket;
    QTcpSocket  *readWriteSocket;
    bool validIPstr(const QString& str);
    waitingDialog* waiting;
};

#endif // MAINWINDOW_H
