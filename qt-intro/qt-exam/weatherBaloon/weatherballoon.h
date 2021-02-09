#ifndef WEATHERBALLOON_H
#define WEATHERBALLOON_H
#include <QWidget>
#include <QPushButton>
#include <QtNetwork/QUdpSocket>
#include <QTimer>
#include <QDateTime>
namespace Ui {
    class weatherBalloon;
}
class weatherBalloon : public QWidget
{
    Q_OBJECT
public:
    explicit weatherBalloon(QWidget *parent = 0);
    ~weatherBalloon();
private slots:
    void processPendingDatagrams();
    void sendDatagram();
private:
    Ui::weatherBalloon *ui;
    QUdpSocket udpSocket;
    QTimer timer;
    double temperature;
    double humidity;
    double altitude;
};
#endif // WEATHERBALLOON_H
