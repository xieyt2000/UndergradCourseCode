#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include"chessboardsquare.h"
#include<QVector>
#include<QStringList>

class chessBoard
{
public:
    QVector<chessPiece> whitePieces;
    QVector<chessPiece> blackPieces;
    chessBoard();
    QVector<QVector<chessBoardSquare>> squares;
    void SetBoardDefault();
};

#endif // CHESSBOARD_H
