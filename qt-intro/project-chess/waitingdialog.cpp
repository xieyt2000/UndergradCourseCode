#include "waitingdialog.h"
#include "ui_waitingdialog.h"

waitingDialog::waitingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waitingDialog)
{
    ui->setupUi(this);
}

waitingDialog::~waitingDialog()
{
    delete ui;
}
