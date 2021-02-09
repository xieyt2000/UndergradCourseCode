#include "promotedialog.h"
#include "ui_promotedialog.h"

promoteDialog::promoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::promoteDialog)
{
    ui->setupUi(this);
}

promoteDialog::~promoteDialog()
{
    delete ui;
}

void promoteDialog::on_buttonBox_accepted()
{
    QString tmp=ui->comboBox->currentText();
    emit proType(tmp);
}
