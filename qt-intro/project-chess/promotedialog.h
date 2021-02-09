#ifndef PROMOTEDIALOG_H
#define PROMOTEDIALOG_H

#include <QDialog>

namespace Ui {
class promoteDialog;
}

class promoteDialog : public QDialog
{
    Q_OBJECT

signals:
    void proType(QString t);

public:
    explicit promoteDialog(QWidget *parent = nullptr);
    ~promoteDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::promoteDialog *ui;
};

#endif // PROMOTEDIALOG_H
