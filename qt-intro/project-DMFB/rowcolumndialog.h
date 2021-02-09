#ifndef ROWCOLUMNDIALOG_H
#define ROWCOLUMNDIALOG_H

#include <QDialog>

namespace Ui {
class rowColumnDialog;
}

class rowColumnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit rowColumnDialog(QWidget *parent = nullptr);
    ~rowColumnDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::rowColumnDialog *ui;

signals:
    void rowColumPut(int r, int c);
};

#endif // ROWCOLUMNDIALOG_H
