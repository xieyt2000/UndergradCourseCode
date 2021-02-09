#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>

namespace Ui {
class MainWindow;
}

enum foodType{biscuit,steak, cola, noodle};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void setImgAndPlaySound(foodType);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer* timer;
    foodType curFood=cola;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void timeoutUpdate();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
