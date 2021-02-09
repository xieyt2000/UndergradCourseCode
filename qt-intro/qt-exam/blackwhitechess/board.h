#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include<QVector>
#include<QRect>
#include<QEvent>
#include<QMouseEvent>
class board : public QWidget
{
    Q_OBJECT
public:
    explicit board(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent* event);

signals:


public slots:
    void reset();

private:
    void paintEvent(QPaintEvent *ev);
    bool endBoard[10][10];//false black true white
    QVector<QVector<QRect>> frontRect;
    QVector<QVector<QRect>> chessRect;
};

#endif // BOARD_H
