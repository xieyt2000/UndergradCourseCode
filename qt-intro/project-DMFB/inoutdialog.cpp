#include "inoutdialog.h"
#include "ui_inoutdialog.h"
#include<QString>
#include<QStringList>

inOutDialog::inOutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inOutDialog)
{
    ui->setupUi(this);
}

inOutDialog::~inOutDialog()
{
    delete ui;
}

posXY inOutDialog::exeuText(QLineEdit* in)
{
    posXY ret(0,0);
    try{
        QString tmp=in->text();
        QStringList tmplist=tmp.split(" ");
        if(tmplist.length()!=2) return ret;
        QRegExp re("\\d*");
        if (re.exactMatch(tmplist[0])&&re.exactMatch(tmplist[1]))
        {
            ret.first=tmplist[0].toInt();
            ret.second=tmplist[1].toInt();
        }
    } catch(...) {
        ret=posXY(0,0);
    }
    return ret;
}

void inOutDialog::on_buttonBox_accepted()
{
    QVector<posXY> input;
    posXY output;
    output=exeuText(ui->lineEdit);
    input.append(exeuText(ui->lineEdit_0));
    input.append(exeuText(ui->lineEdit_2));
    input.append(exeuText(ui->lineEdit_3));
    input.append(exeuText(ui->lineEdit_4));
    input.append(exeuText(ui->lineEdit_5));
    input.append(exeuText(ui->lineEdit_6));
    input.append(exeuText(ui->lineEdit_7));
    input.append(exeuText(ui->lineEdit_8));
    input.append(exeuText(ui->lineEdit_9));
    input.append(exeuText(ui->lineEdit_10));
    input.append(exeuText(ui->lineEdit_11));
    input.append(exeuText(ui->lineEdit_12));
    input.append(exeuText(ui->lineEdit_13));
    emit inOutPut(input, output);
}


