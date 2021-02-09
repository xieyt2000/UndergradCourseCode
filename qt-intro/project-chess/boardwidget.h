#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include"chessboard.h"
#include<QPaintEvent>
#include<QPainter>
#include<QPixmap>
#include<QRect>
#include<QMouseEvent>
#include<QTimer>

enum castleSide{kingside, queenside};

class boardWidget : public QWidget
{
    Q_OBJECT
private:
    chessBoard board;
    QPixmap getPixMap(chessPieceType type, chessSide side);
    QVector<QVector<QRect>> frontRects;//make sure frontRects follow the order of board
    bool selectAPiece=false;
    chessPos curSelectedPiecePos;
    chessPiece curSelectedPiece;
    void genSelectAble(const chessPiece& piece, const chessPos& pos);
    chessSide curSide=whiteSide;
    bool promotePawn(chessPos pos);
    void oneSideWin(chessSide winSide);
    chessSide getOtherSide(chessSide thisSide);
    chessPieceType getType(QString type);

    void checkStatus(chessSide sideToCheck);
    bool checkCheck(chessSide sideToCheck);//return check or not
    bool checkStalemate(chessSide sideToCheck);//return check or not
    void markAllTheSquresOneSideCanGo(chessSide markSide);
    void markAllTheSquresOneSideCanGoExceptKingAndExcludeThemSelves(chessSide markSide);
    bool checkBothSideCheckAndCursideStalement();//if stale return ture
    void resetSelect();
    void resetBoard();
    //bool timerStarted=false;
    int curCountDownTime=60;
    void countDown();

public:
    explicit boardWidget(QWidget *parent = nullptr);
    QTimer mySideTimer;
    chessSide mySide=whiteSide;
    QStringList generateCurBoard();
    bool nowIsMySide();
    void genBoardStrAndSend();
signals:
    void sendBoardMessage(QString str);
    void changeLCDTimer(int val);
public slots:
    void mySideResign();
    void loadABoard(QVector<QStringList> input);//lines
    void mySideOverTime();
    void castling(castleSide);
    void startCountDown();
    void stopCountDown();
protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
};

#endif // BOARDWIDGET_H
