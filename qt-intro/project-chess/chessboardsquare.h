#ifndef CHESSBOARDSQUARE_H
#define CHESSBOARDSQUARE_H
#include"chesspiece.h"

class chessBoardSquare
{
public:
    chessBoardSquare();
    chessPiece chessOnTheBoard;
    bool selectable=false;
    bool hasChess=false;
};

#endif // CHESSBOARDSQUARE_H
