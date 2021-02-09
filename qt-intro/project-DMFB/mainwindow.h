#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"rowcolumndialog.h"
#include"inoutdialog.h"
#include"washdialog.h"

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
    void on_menuRowColumnNum_triggered();
    void on_menuInOutpos_triggered();
    void on_menuCommadFromFile_triggered();
    void on_menuWash2_triggered();

    void on_actionPause_triggered();

    void on_actionRestart_triggered();

private:
    Ui::MainWindow *ui;
    rowColumnDialog* rcD;
    inOutDialog* ioD;
    washDialog* wDialog;
};

#endif // MAINWINDOW_H
