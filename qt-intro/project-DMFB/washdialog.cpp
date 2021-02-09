#include "washdialog.h"
#include "ui_washdialog.h"

washDialog::washDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::washDialog)
{
    ui->setupUi(this);
}

washDialog::~washDialog()
{
    delete ui;
}

void washDialog::on_buttonBox_accepted()
{
    emit washSet(ui->checkBoxWash->checkState());
}
