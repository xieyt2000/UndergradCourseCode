#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QVector>
#include<QRectF>
#include<QPair>
#include"inoutdialog.h"
#include<QString>
#include<QSet>
#include"command.h"
#include"liquiddrop.h"
#include"square.h"

enum soundType{
    movemixSound, mergesuccessSound, split1Sound, split2Sound
};

class board : public QWidget
{
    Q_OBJECT
public:
    explicit board(QWidget *parent = nullptr);

signals:
    void timeChange(int t);

public slots:
    void genRects(int r, int c);
    void genInOut(QVector<posXY>, posXY);
    void readFile(QString path);
    void exeut(int targetTime, int starttime=0);
    void defaultPlay();
    void playNext();
    void playPrev();
    void reset();
    void restart();
    void changePauseStatus();
    void changeSpeed(int newSpeed);
    void setWash(bool wa);
    void washShow();
protected:
    void paintEvent(QPaintEvent*);

private:
    QVector<QRectF> rectsToDraw;
    QVector<QRectF> rectsEdge;
    QRectF& getEdgeRec(int x, int y);
    QRectF& getSquareRec(int x, int y);
    int row=-1, column=-1;
    QVector<posXY> inputs;
    posXY output=posXY(0,0);
    posXY washIn;
    posXY washOut;
    void dialogWarning(QString text);
    int wid;
    int hei;
    QVector<QVector<command>> cmdlist;
    QVector<liquidDrop> liquidDrops;
    int CurTime=-1;
    QVector<QVector<QVector<square>>> endBoards;
    QVector<QVector<square>> curEndBoard;
    bool checkAdj();
    int findLiquidIndexByID(int id);
    void resetEndBoard();
    int totaltime=0;
    bool isPause=false;
    QVector<QSet<soundType>> sounds;
    int distanceCheck(int k); //return the wrong step, if all right return -1
    posXY findLiquidOnBoard(int id, const QVector<QVector<square>>& bdToFind);
    bool isRest=false;
    bool posInBoardRange(posXY);
    int playSpeed = 1000; //from 500 to 1500  default 1000
    bool wash=false;
    bool washLimit=false;
    int liquidDropIdCount=0;
    void mousePressEvent(QMouseEvent* event);
};

#endif // BOARD_H
