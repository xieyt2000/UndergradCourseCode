#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->clear();
    path="";
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog* fileDialog=new QFileDialog(this);
    if(fileDialog->exec() == QDialog::Accepted) {
        path = fileDialog->selectedFiles()[0];
        QFile* file=new QFile(path);
        if(file->open(QFile::ReadOnly))
        {
            QTextStream in(file);
            ui->textEdit->setText(in.readAll());
        }
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionSave_triggered()
{
    if(path=="")
    {
        QFileDialog* fileDialog=new QFileDialog(this);
        if(fileDialog->exec() == QDialog::Accepted) {
            path = fileDialog->selectedFiles()[0];
        }
    }
    QFile file(path);
       if(file.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QTextStream textStream(&file);
           QString str = ui->textEdit->toPlainText();
           textStream<<str;
           file.close();
       }
}
