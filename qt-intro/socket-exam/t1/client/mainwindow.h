#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpSocket>
#include<QHostAddress>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectToHost();

signals:
    void textChange(QString txt);
private slots:
    void on_pushButton_clicked();
    void getfile();
    void changeText(QString txt);
private:
    Ui::MainWindow *ui;
    QString source;
    QString target;
    QTcpSocket* socket;
    bool readone=true;
    //QThread th1;
};

#endif // MAINWINDOW_H
