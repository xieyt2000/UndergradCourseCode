#ifndef WASHDIALOG_H
#define WASHDIALOG_H

#include <QDialog>

namespace Ui {
class washDialog;
}

class washDialog : public QDialog
{
    Q_OBJECT

public:
    explicit washDialog(QWidget *parent = nullptr);
    ~washDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void washSet(bool wash);

private:
    Ui::washDialog *ui;
};

#endif // WASHDIALOG_H
