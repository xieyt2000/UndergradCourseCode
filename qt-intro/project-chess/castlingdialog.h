#ifndef CASTLINGDIALOG_H
#define CASTLINGDIALOG_H

#include <QDialog>

namespace Ui {
class castlingDialog;
}

class castlingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit castlingDialog(QWidget *parent = nullptr);
    ~castlingDialog();

signals:
    void chooseKingSide();
    void chooseQueenSide();

private slots:
    void on_pushButtonking_clicked();

    void on_pushButtonqueen_clicked();

private:
    Ui::castlingDialog *ui;
};

#endif // CASTLINGDIALOG_H
