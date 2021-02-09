#include "board.h"
#include<QPainter>
#include<QtDebug>
#include<QMessageBox>

board::board(QWidget *parent) : QWidget(parent)
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            endBoard[i][j]=false;
        }
    }

    frontRect.resize(10);
    chessRect.resize(10);
    for(int i=0;i<10;i++)
    {
        frontRect[i].resize(10);
        chessRect[i].resize(10);
    }
}

void board::mousePressEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton) return;
    //find chess
    int X=event->pos().x(); int Y=event->pos().y();
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            QRect tmpRect=chessRect[i][j];
            if(X>tmpRect.left()&&X<tmpRect.right()&&Y>tmpRect.top()&&Y<tmpRect.bottom())
            {
                if(endBoard[i][j])
                {
                    QMessageBox warDialog;
                    warDialog.setText("Clikc a White Chess");
                    warDialog.exec();
                    return;
                }
                for(int k=1;k<=8;k++)
                {
                    endBoard[i][k]=true;
                    endBoard[k][j]=true;
                }
                update();
            }
        }
    }
    return;
}

void board::reset()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            endBoard[i][j]=false;
        }
    }
    update();
}

void board::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);

    int extent;
    if (width()>height())
        extent = height()-10;
    else
        extent = width()-10;
    p.setBrush(Qt::yellow);
    p.drawRect(0,0,extent,extent);
    int rectLenth=extent/8;

    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            frontRect[i][j]=QRect((i-1)*rectLenth,(j-1)*rectLenth,rectLenth,rectLenth);
            chessRect[i][j]=QRect((i-0.9)*rectLenth,(j-0.9)*rectLenth,0.8*rectLenth,0.8*rectLenth);
        }
    }
    for(auto i : frontRect)
    {
        p.drawRects(i);
    }
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            qDebug()<<"fuck";
            if(endBoard[i][j])
            {
                p.setPen(Qt::white);
                p.setBrush(Qt::white);
                p.drawEllipse(chessRect[i][j]);
            }
            else
            {
                p.setPen(Qt::black);
                p.setBrush(Qt::black);
                p.drawEllipse(chessRect[i][j]);
            }
        }
    }
}
