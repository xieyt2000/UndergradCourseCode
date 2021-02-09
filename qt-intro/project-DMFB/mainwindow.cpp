#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rowcolumndialog.h"
#include"inoutdialog.h"
#include<qinputdialog.h>
#include<QtDebug>
#include"washdialog.h"
#include<QLCDNumber>
#include<QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->DMFBboard, SIGNAL(timeChange(int)) , ui->lcdNumber, SLOT(display(int)));
    connect(ui->actionDefaultPlay, &QAction::triggered, ui->DMFBboard, &board::defaultPlay);
    connect(ui->actionNext, &QAction::triggered, ui->DMFBboard, &board::playNext);
    connect(ui->actionPrevious, &QAction::triggered, ui->DMFBboard, &board::playPrev);
    connect(ui->actionReset, &QAction::triggered, ui->DMFBboard, &board::reset);
    //connect(ui->actionRestart, &QAction::triggered, ui->DMFBboard, &board::restart);
    connect(ui->actionPause, &QAction::triggered, ui->DMFBboard, &board::changePauseStatus);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_menuRowColumnNum_triggered()
{
    rcD=new rowColumnDialog(this);
    connect(rcD, &rowColumnDialog::rowColumPut, ui->DMFBboard, &board::genRects);
    rcD->show();
}

void MainWindow::on_menuInOutpos_triggered()
{
    ioD=new inOutDialog(this);
    connect(ioD, &inOutDialog::inOutPut, ui->DMFBboard, &board::genInOut);
    ioD->show();
}

void MainWindow::on_menuCommadFromFile_triggered()
{
    QInputDialog* fileDialog=new QInputDialog(this);
    fileDialog->setLabelText("文件路径");
    connect(fileDialog, &QInputDialog::textValueSelected, ui->DMFBboard, &board::readFile);
    fileDialog->show();
}

void MainWindow::on_menuWash2_triggered()
{
    wDialog=new washDialog(this);
    connect(wDialog, &washDialog::washSet, ui->DMFBboard, &board::setWash);
    wDialog->show();
}


void MainWindow::on_actionPause_triggered()
{
    if(ui->actionPause->text()=="继续")
    {
        ui->actionPause->setText("暂停");
    }
    else {
        ui->actionPause->setText("继续");
    }
}

void MainWindow::on_actionRestart_triggered()
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());

}
