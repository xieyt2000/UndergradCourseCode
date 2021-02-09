#ifndef INOUTDIALOG_H
#define INOUTDIALOG_H

#include <QDialog>
#include<QLineEdit>

typedef QPair<int, int> posXY;
namespace Ui {
class inOutDialog;
}

class inOutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit inOutDialog(QWidget *parent = nullptr);
    ~inOutDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void inOutPut(QVector<posXY>, posXY);

private:
    Ui::inOutDialog *ui;
    posXY exeuText(QLineEdit* in);
};

#endif // INOUTDIALOG_H
