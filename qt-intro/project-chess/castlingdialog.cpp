#include "castlingdialog.h"
#include "ui_castlingdialog.h"

castlingDialog::castlingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::castlingDialog)
{
    ui->setupUi(this);
}

castlingDialog::~castlingDialog()
{
    delete ui;
}

void castlingDialog::on_pushButtonking_clicked()
{
    this->close();
    emit chooseKingSide();
}

void castlingDialog::on_pushButtonqueen_clicked()
{
    this->close();
    emit chooseQueenSide();
}
