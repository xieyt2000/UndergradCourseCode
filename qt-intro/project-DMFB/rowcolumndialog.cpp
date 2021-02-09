#include "rowcolumndialog.h"
#include "ui_rowcolumndialog.h"
#include<QDebug>

rowColumnDialog::rowColumnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rowColumnDialog)
{
    ui->setupUi(this);
}

rowColumnDialog::~rowColumnDialog()
{
    delete ui;
}

void rowColumnDialog::on_buttonBox_accepted()
{
    emit rowColumPut(ui->rowspinBox->value(), ui->columnspinBox->value());
}
